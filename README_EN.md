This is an automatic translation, may be incorrect in some places. See sources and examples!

#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0% B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square )](https://alexgyver.ru/support_alex/)

[![Foo](https://img.shields.io/badge/README-ENGLISH-brightgreen.svg?style=for-the-badge)](https://github-com.translate.goog/GyverLibs/ BitPack?_x_tr_sl=ru&_x_tr_tl=en)

#bitpack
Library for packing bit flags into a byte array (saving space) for Arduino

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **BitPack** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/BitPack/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
// specify the number of flags
BitPack<10> flags;
```

<a id="usage"></a>
## Usage
```cpp

void set(uint8_tnum);// install
void clear(uint8_t num); // reset
void toggle(uint8_t num); // toggle
void write(uint8_t num, bool state); // write
bool read(uint8_t num); // read
void setAll(); // install all
void clearAll(); // reset everything
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include "BitPack.h"

// specify the number of flags
BitPack<10> flags;

void setup() {
  Serial.begin(9600);
  flags.clearAll(); // omit everything
  flags set(1); // raise the flag
  flags set(3);
  flags.write(3, 1);
  Serial.println(flags.read(0)); // read the flag
  Serial.println(flags.read(1));
  Serial.println(flags.read(2));
  flags[3] = 0; // can be written via []
  Serial.println(flags[3]); // can be read via []
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!