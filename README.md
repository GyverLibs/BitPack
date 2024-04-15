[![latest](https://img.shields.io/github/v/release/GyverLibs/BitPack.svg?color=brightgreen)](https://github.com/GyverLibs/BitPack/releases/latest/download/BitPack.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/BitPack.svg)](https://registry.platformio.org/libraries/gyverlibs/BitPack)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/BitPack.svg)](https://registry.platformio.org/libraries/gyverlibs/BitPack)
[![arduino-library](https://www.ardu-badge.com/badge/BitPack.svg?)](https://www.ardu-badge.com/BitPack)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/BitPack?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# BitPack
Библиотека для упаковки битовых флагов в байтовый массив (экономия места) для Arduino

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="init"></a>
## Инициализация

```cpp
// указываем количество флагов
BitPack<10> pack;     // static буфер внутри
BitPackDyn pack(10);  // динамическое выделение

uint8_t buf[2]; // 1 байт - 8 флагов
BitPackExt pack(buf, 10);  // 10 флагов
```

<a id="usage"></a>
## Использование

```cpp
// методы
void set(uint16_t num);                  // установить
void clear(uint16_t num);                // сбросить
void toggle(uint16_t num);               // переключить
void write(uint16_t num, bool state);    // записать
bool read(uint16_t num);                 // прочитать
void setAll();                          // установить все
void clearAll();                        // сбросить все
bool copyTo(любой пак);                 // копировать в    
bool copyFrom(любой пак);               // копировать из

uint16_t amount();                      // количество флагов
uint16_t size();                        // размер pack в байтах

uint8_t* pack;                          // доступ к буферу

// макросы
BP_SET(pack, idx)
BP_CLEAR(pack, idx)
BP_READ(pack, idx)
BP_TOGGLE(pack, idx)
BP_WRITE(pack, idx)

// настройки (до подключения библиотеки)
#define BP_NO_ARRAY   // убрать доступ через [] - экономит 2 байта RAM
```

### Доступ через []
В библиотеке реализован удобный доступ к битам через образение как к массиву `[]`. Этот способ *чуть медленнее* использования функций set/read/write!
```cpp
BitPack<10> flags;
flags[0] = 1;
Serial.println(flags[0]);
bool f = flags[0];

BitPack<10> flags2;
flags[0] = flags2[0];

// примечание:
// такое приравнивание некорректно! Используй copyTo/copyFrom
flags = flags2;

flags.copyTo(flags2);     // копировать весь пакет
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

  flags[3] = 0;				      // можно писать через []
  Serial.println(flags[3]); // можно читать через []

  BitPack<10> flags2;
  flags[0] = flags2[1];     // копировать бит
  flags.copyTo(flags2);     // копировать весь пакет
}

void loop() {
}
```

<a id="versions"></a>

## Версии
- v1.0
- v1.1 - пофикшен доступ через [], добавлены новые инструменты
- v1.1.1 - перезалив
- v1.2 - добавлены copy методы, упрощён доступ через массив

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
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
