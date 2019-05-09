void timersTick() {   // каждую секунду
  // получаем время
  now = rtc.now();
  realTime[0] = now.hour();
  realTime[1] = now.minute();
  realTime[2] = now.second();
  uptime += (float)0.0000115741;   // аптайм у нас в сутках! 1/(24*60*60)

  for (byte curChannel = 0; curChannel < 10; curChannel++) {
    if (channels[curChannel].state       // если канал активен (on/off)
        && (curChannel >= 7 || (curChannel < 7 && channels[curChannel].relayType != 2) ) ) {   // для всех кроме ОБЩИХ реле
      switch (channels[curChannel].mode) {
        case 0:   // ---------------------- если таймер ----------------------
          if (millis() - timerMillis[curChannel] >= channels[curChannel].period * 1000
              && channelStates[curChannel] != channels[curChannel].direction) {
            timerMillis[curChannel] = millis();
            channelStates[curChannel] = channels[curChannel].direction;
          }
          if (millis() - timerMillis[curChannel] >= channels[curChannel].work * 1000
              && channelStates[curChannel] == channels[curChannel].direction) {
            channelStates[curChannel] = !channels[curChannel].direction;
          }
          break;
        case 1:   // ---------------------- если таймер RTC ----------------------
          if (realTime[2] == 0 || realTime[2] == 1) {                               // проверка каждую минуту (в первые две секунды, на всякий случай)!
            if (channels[curChannel].impulsePrd < 6) {                              // если минутные периоды
              if (channelStates[curChannel] != channels[curChannel].direction) {    // если канал ВЫКЛЮЧЕН
                byte waterTime = 0;                                                 // начало проверки времени с 0 минуты
                for (byte j = 0; j < 60 / impulsePrds[channels[curChannel].impulsePrd]; j++) {
                  if (realTime[1] == waterTime) {
                    channelStates[curChannel] = channels[curChannel].direction;     // ВКЛЮЧАЕМ
                    timerMillis[curChannel] = millis();                             // взводим таймер
                  }
                  waterTime += impulsePrds[channels[curChannel].impulsePrd];
                }
              }
            } else {                                                                // если часовые периоды
              if (channelStates[curChannel] != channels[curChannel].direction) {    // если ВЫКЛЮЧЕН
                byte waterTime = channels[curChannel].startHour;                    // начало проверки времени со стартового часа
                for (byte j = 0; j < 24 / impulsePrds[channels[curChannel].impulsePrd]; j++) {
                  if (waterTime < 24) {
                    if (realTime[0] == waterTime) {
                      channelStates[curChannel] = channels[curChannel].direction;   // ВКЛЮЧАЕМ
                      timerMillis[curChannel] = millis();                           // взводим таймер
                    }
                  } else {
                    if (realTime[0] == waterTime - 24) {
                      channelStates[curChannel] = channels[curChannel].direction;   // ВКЛЮЧАЕМ
                      timerMillis[curChannel] = millis();                           // взводим таймер
                    }
                  }
                  waterTime += impulsePrds[channels[curChannel].impulsePrd];
                }
              }
            }
          }

          if (channelStates[curChannel] == channels[curChannel].direction                     // если ВКЛЮЧЕН
              && millis() - timerMillis[curChannel] >= channels[curChannel].work * 1000) {    // И отработал время РАБОТА
            channelStates[curChannel] = !channels[curChannel].direction;                      // ВЫКЛЮЧАЕМ
          }
          break;
        case 2:   // ---------------------- если сутки ----------------------
          if (channelStates[curChannel] != channels[curChannel].direction
              && (realTime[0] >= channels[curChannel].hour1 && realTime[0] < channels[curChannel].hour2) ) {
            channelStates[curChannel] = channels[curChannel].direction;
          } else if (channelStates[curChannel] == channels[curChannel].direction
                     && (realTime[0] < channels[curChannel].hour1 || realTime[0] >= channels[curChannel].hour2)) {
            channelStates[curChannel] = !channels[curChannel].direction;
          }
          break;
        case 3:   // ---------------------- если датчик ----------------------
          if (millis() - timerMillis[curChannel] >= channels[curChannel].sensPeriod * 1000L) {
            timerMillis[curChannel] = millis();
            if (sensorVals[channels[curChannel].sensor] > channels[curChannel].threshold)
              channelStates[curChannel] = channels[curChannel].direction;
            else
              channelStates[curChannel] = !channels[curChannel].direction;
          }
          break;
      }
    }
  }

  // --- применяем ---

  // реле
  boolean atLeastOneValve = false;                              // флаг "хотя бы одного" клапана
  for (byte relay = 0; relay < 7; relay++) {
    if (channels[relay].relayType == 1                          // если реле - КЛАПАН
        && channelStates[relay] == channels[relay].direction)   // и он ВКЛЮЧЕН
      atLeastOneValve = true;                                   // запоминаем, что нужно включить общий канал
    digitalWrite(relayPins[relay], channelStates[relay]);       // включаем/выключаем все реле типов РЕЛЕ и КЛАПАН
  }

  for (byte relay = 0; relay < 7; relay++) {
    if (channels[relay].relayType == 2) {                 // только для ОБЩИХ каналов реле
      if (atLeastOneValve) channelStates[relay] = channels[relay].direction;  // включить общий
      else channelStates[relay] = !channels[relay].direction;                 // выключить общий
      digitalWrite(relayPins[relay], channelStates[relay]);                   // применить
    }
  }

  // серво
  if (channelStates[7]) servoPos[0] = minAngle[0];
  else servoPos[0] = maxAngle[0];
  if (channelStates[8]) servoPos[1] = minAngle[1];
  else servoPos[1] = maxAngle[1];

  if (channels[7].state) servo1.setTargetDeg(servoPos[0]);
  if (channels[8].state) servo2.setTargetDeg(servoPos[1]);

  // привод
  if (lastDriveState != channelStates[9]) {
    lastDriveState = channelStates[9];
    driveState = 1;
  }
}

void driveTick() {
  if (channels[9].state || serviceFlag || manualControl) {
    if (driveState == 1) {
      driveState = 2;
      driveTimer = millis();
      boolean thisDirection;
      thisDirection = channelStates[9];
      if (serviceFlag) thisDirection = channelStatesServ[9];      
      if (manualControl) thisDirection = manualPos;
      
      if (thisDirection) {
        digitalWrite(DRV_SIGNAL1, !DRIVER_LEVEL);
        digitalWrite(DRV_SIGNAL2, DRIVER_LEVEL);
      } else {
        digitalWrite(DRV_SIGNAL1, DRIVER_LEVEL);
        digitalWrite(DRV_SIGNAL2, !DRIVER_LEVEL);
      }
    }
    if (driveState == 2 && millis() - driveTimer >= ((long)driveTimeout * 1000)) {
      driveState = 0;
      digitalWrite(DRV_SIGNAL1, DRIVER_LEVEL);
      digitalWrite(DRV_SIGNAL2, DRIVER_LEVEL);
      manualControl = false;
    }
  }
}

uint32_t sensorTimer;
uint32_t period;
byte sensorMode = 0;
void readAllSensors() {
  if (millis() - sensorTimer >= period) {
    sensorTimer = millis();
    switch (sensorMode) {
      case 0:   // вкл питание
        sensorMode = 1;
        period = 100;
        digitalWrite(SENS_VCC, 1);
        break;
      case 1:   // измеряем
        sensorMode = 2;
        period = 25;
        //float temp(NAN), hum(NAN), pres(NAN);
        //bme.read(pres, temp, hum, BME280::TempUnit_Celsius, BME280::PresUnit_Pa);
        //double temperature, pressure;
        //double humidity = bme.readHumidity(temperature, pressure);
        // (air temp, air hum, mois1...)
        sensorVals[0] = floor(bme.readTemperature());
        sensorVals[1] = floor(bme.readHumidity());
        sensorVals[2] = analogRead(SENS_0);
        sensorVals[3] = analogRead(SENS_1);
        sensorVals[4] = analogRead(SENS_2);
        sensorVals[5] = analogRead(SENS_3);
        break;
      case 2:   // выключаем
        sensorMode = 0;
        period = (long)comSensPeriod * 1000;
        digitalWrite(SENS_VCC, 0);
        break;
    }
  }
}

void plotTick() {
  if (millis() - plotTimer >= 5760000) {  // каждые 1.6 часа (график за 24 часа, разрешение 1.6 часа)
    // сдвигаем массивы
    for (byte i = 0; i < 14; i++) {
      tempDay[i] = tempDay[i + 1];
      humDay[i] = humDay[i + 1];
      sensDay_0[i] = sensDay_0[i + 1];
      sensDay_1[i] = sensDay_1[i + 1];
      sensDay_2[i] = sensDay_2[i + 1];
      sensDay_3[i] = sensDay_3[i + 1];
    }

    // обновляем крайний элемент
    tempDay[14] = sensorVals[0];
    humDay[14] = sensorVals[1];
    sensDay_0[14] = sensorVals[2];
    sensDay_1[14] = sensorVals[3];
    sensDay_2[14] = sensorVals[4];
    sensDay_3[14] = sensorVals[5];
  }
}
