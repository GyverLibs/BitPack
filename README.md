![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# BitPack
Библиотека для упаковки битовых флагов в байтовый массив (экономия места) для Arduino

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **BitPack** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/BitPack/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
// указываем количество флагов
BitPack<10> flags;
```

<a id="usage"></a>
## Использование
```cpp

void set(uint8_t num);                  // установить
void clear(uint8_t num);                // сбросить
void toggle(uint8_t num);               // переключить
void write(uint8_t num, bool state);    // записать
bool read(uint8_t num);                 // прочитать
void setAll();                          // установить все
void clearAll();                        // сбросить все
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
#include "BitPack.h"

// указываем количество флагов
BitPack<10> flags;

void setup() {
  Serial.begin(9600);
  flags.clearAll(); // опустить все
  flags.set(1);     // поднять флаг
  flags.set(3);
  flags.write(3, 1);
  Serial.println(flags.read(0));  // прочитать флаг
  Serial.println(flags.read(1));
  Serial.println(flags.read(2));
  flags[3] = 0;				// можно писать через []
  Serial.println(flags[3]); // можно читать через []
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!