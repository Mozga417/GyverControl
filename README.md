![PROJECT_PHOTO](https://github.com/AlexGyver/gyverControl/blob/master/proj_img.jpg)
# Универсальный контроллер умной теплицы
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
**GyverControl** - универсальный контроллер-таймер для теплицы и других мест, где нужна автоматизация по таймеру или показателям микроклимата/другим датчикам. Ссылки на все компоненты, схемы, инструкции и другая информация находятся на странице проекта на официальном сайте: https://alexgyver.ru/gyvercontrol/.  
   
#### Особенности:
- 7 каналов с логическим выходом 5V, к которым можно подключать обычное реле, твердотельное реле, силовые ключи (транзисторы, модули на основе транзисторов)
- 2 канала сервоприводов, подключаются обычные модельные серво больших и маленьких размеров
- 1 канал управления линейным электроприводом с концевиками ограничения движения и с работой по тайм-ауту
- Датчик температуры воздуха (BME280)
- Датчик влажности воздуха (BME280)
- 4 аналоговых датчика (влажности почвы или других)
- Модуль опорного (реального) времени RTC DS3231 с автономным питанием
- Большой LCD дисплей (LCD 2004, 20 столбцов, 4 строки)
- Орган управления - энкодер
- Периодичный полив (реле)
- Схема с индивидуальными помпами/клапанами
- Схема с одной помпой и несколькими клапанами
- Полив на основе показаний датчиков влажности почвы
- Управление освещением (реле) с привязкой ко времени суток
- Проветривание (привод открывает окно/серво открывает заслонку) по датчику температуры или влажности воздуха
- Увлажнение (включение увлажнителя) по датчику влажности воздуха
- Обогрев (включение обогревателя) по датчику температуры
- Выполнение действий сервоприводом (нажатие кнопок на устройствах, поворот рукояток, поворот заслонок, перемещение предметов) по датчику или таймеру

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки для Arduino
- **schemes** - схемы подключения компонентов
- **docs** - документация, картинки
- **PCB** - файлы печатной платы

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/gyverControl/blob/master/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/gyverControl/blob/master/PCB/PCBmap.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
Arduino NANO 328p – искать
* https://ali.ski/tI7blh
* https://ali.ski/O4yTxb
* https://ali.ski/6_rFIS
* https://ali.ski/gb92E-
Энкодер – искать
* https://ali.ski/c-hjE
* https://ali.ski/OygY3d
* https://ali.ski/II_efl
* Дисплей 2004 https://ali.ski/LTT9-
* DS3231 мини https://ali.ski/dU04gz
* Датчик т/вл воздуха BME280 (5V) https://ali.ski/S0luA
* Драйвер привода https://ali.ski/1EhPr
Датчики вл. почвы

* Обычный https://ali.ski/m8BeF
* Золотой https://ali.ski/-bsqJ
* Ёмкостный https://ali.ski/M6VDH
Аналоговые датчики

* Освещённости https://ali.ski/Lnf83U
* Термистор https://ali.ski/uW2Yr
* Звука https://ali.ski/iRQ5N
* ИК излучения https://ali.ski/osmF7u
* Дождя https://ali.ski/lVpLJe
* Уровня воды https://ali.ski/dx5WBl
* Газоанализатор https://ali.ski/uPCLr
Модули реле

* Обычные https://ali.ski/9HO–D
* Твердотельные https://ali.ski/RXOMz
* Одноканальное мощное SSR https://ali.ski/Q7p4F7
Сервоприводы

* Малый (2 кг*см) https://ali.ski/A-9ge
* Большой (13 кг*см) https://ali.ski/TCkbH
* Большой (20 кг*см) https://ali.ski/6Zm1t
* Очень большой (60 кг*см) https://ali.ski/TEndsx
Линейные приводы

* Привод 100мм 12V (скорость я брал 45mm/s) http://ali.ski/nLdJOj
Железки для теплицы

Средняя помпа
* https://ali.ski/XR-Nd
* https://ali.ski/pnFE6
Мощная помпа
* https://ali.ski/pn_aq
* https://ali.ski/LBRNq0
* https://ali.ski/0nggzk
* https://ali.ski/9yTPR
* Клапан 1/2″ https://ali.ski/BLmah
Лампочки с полным спектром
* http://ali.ski/AXzAf
* ttp://ali.ski/8Qi8a0
* Матрицы с полным спектром https://ali.ski/k-WPS6
* Готовые полноспектровые светильники https://ali.ski/NHgOk
Разное

* БП 5V 2A питание схемы https://ali.ski/uMcMWP
* БП 12V 3A питание привода http://ali.ski/7iOfQn http://ali.ski/ygpCU  http://ali.ski/qrJ41
* Кнопки искать https://ali.ski/PrsxZ
* Кнопки NC http://ali.ski/GmyPb
* Кнопки NO http://ali.ski/vk-rb
* Концевик герметичный http://ali.ski/MTxcf http://ali.ski/g655sn
* Колодки https://ali.ski/uQdWqO
* Рейка контактная https://ali.ski/4n0EH
* Рейка угловая http://fas.st/opqeGu
* В наших магазинах

* Рейка контактная https://www.chipdip.ru/product/pls-40
* Рейка угловая тройная PLT-120R https://www.chipdip.ru/product/plt-120r-pitch-2-54-mm

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    #define ENCODER_TYPE 1      // тип энкодера (0 или 1). Если энкодер работает некорректно (пропуск шагов/2 шага), смените тип
    #define ENC_REVERSE 0       // 1 - инвертировать направление энкодера, 0 - нет
    #define DRIVER_LEVEL 1      // 1 или 0 - уровень сигнала на драйвер/реле для привода
    #define LCD_ADDR 0x3f       // адрес дисплея 0x27 или 0x3f . Смени если не работает!!
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)