This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/BitPack.svg?color=brightgreen)](https://github.com/GyverLibs/BitPack/releases/latest/download/BitPack.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/BitPack.svg)](https://registry.platformio.org/libraries/gyverlibs/BitPack)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/BitPack?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# BitPack
Library for packing bit flags into byte array (space saving) for Arduino

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Installation](#install)
- [Bugs and feedback](#feedback)

<a id="init"></a>
## Initialization

```cpp
// indicate the number of flags
BitPack<10> pack;     // static buffer inside
BitPackDyn pack(10);  // discharge

uint8_t buf[2]; // 1 byte - 8 flags
BitPackExt pack(buf, 10);  // 10 flags
```

<a id="usage"></a>
## Use of use

```cpp
// method
void set(uint16_t num);                  // set up
void clear(uint16_t num);                // drop off
void toggle(uint16_t num);               // switch off
void write(uint16_t num, bool state);    // write down
bool read(uint16_t num);                 // read
void setAll();                          // set up
void clearAll();                        // drop off
bool copyTo(любой пак);                 // copy
bool copyFrom(любой пак);               // copy

uint16_t amount();                      // number
uint16_t size();                        // pack-size

uint8_t* pack;                          // buffering

// macro
BP_SET(pack, idx)
BP_CLEAR(pack, idx)
BP_READ(pack, idx)
BP_TOGGLE(pack, idx)
BP_WRITE(pack, idx)

// settings (before the library is connected)
#define BP_NO_ARRAY   // Remove access via [] - saves 2 bytes of RAM
```

#### BitPackExt
```cpp
BitPackExt() {}

// transfer the buffer and its size in the number of flags (8 flags - 1 byte)
BitPackExt(uint8_t* pack, uint16_t amount, bool clear = true);

// transfer the buffer and its size in the number of flags (8 flags - 1 byte)
void setBuffer(uint8_t* pack, uint16_t amount, bool clear = true);
```

#### BitPackDyn
```cpp
BitPackDyn() {}

// number of flags
BitPackDyn(uint16_t amount);

// number of flags
void init(uint16_t amount);
```

### Access via []
The library has convenient access to bits through formation as an array`[]`. This is a slightly slower way to use set/read/write!
```cpp
BitPack<10> flags;
flags[0] = 1;
Serial.println(flags[0]);
bool f = flags[0];

BitPack<10> flags2;
flags[0] = flags2[0];

// note:
// This equation is incorrect! Use copyTo/copyFrom
flags = flags2;

flags.copyTo(flags2);     // copy
```

### BitFlags
```cpp
// flag-pack
T flags{};

// mask
void set(const T mask);

// mask
void clear(const T mask);

// mask
void write(const T mask, const bool val);

// mask
void writeBits(const T mask, const T bits);

// mask
T read(const T mask);

// all the bats in the mask
bool isSet(const T mask);

// stripped all the bits in the mask
bool isClear(const T mask);

// match n
bool compare(const T mask, const T val);
```

Three more packets of a fixed number of flags`BitFlags8`, `BitFlags16`, `BitFlags32`8/16/32 flags respectively. They work a little differently than registers. You can set and read several flags in one action, which greatly improves performance. For convenience, flags can be declared as bits:
```cpp
#define MY_FLAG_0 bit(0)
#define KEK_FLAG bit(1)
#define SOME_F bit(2)

BitFlags8 flags;
flags.set(KEK_FLAG | SOME_F);       // double-flag
if (flags.read(KEK_FLAG | SOME_F)); // check out

// Compare takes the mask from the first argument and compares it to the second.
// In fact, the meaning is this: the definition of a situation where only certain flags are raised from these flags.
// KEK FLAG and SOME F flags only SOME F (KEK FLAG omitted)
if (flags.compare(KEK_FLAG | SOME_F, SOME_F));
```

<a id="example"></a>
## Example
For more examples see **examples**!

```cpp
#include "BitPack.h"

// indicate the number of flags
BitPack<10> flags;

void setup() {
  Serial.begin(9600);
  flags.clearAll(); // drop everything
  flags.set(1);     // flag
  flags.set(3);
  flags.write(3, 1);
  Serial.println(flags.read(0));  // flag
  Serial.println(flags.read(1));
  Serial.println(flags.read(2));

  flags[3] = 0;				      // You can write through [...]
  Serial.println(flags[3]); // can be read through []

  BitPack<10> flags2;
  flags[0] = flags2[1];     // copy
  flags.copyTo(flags2);     // copy
}

void loop() {
}
```

<a id="versions"></a>

## Versions
- v1.0
- v1.1 - Fixed access via [], new tools added
- v1.1.1. - refill
- v1.2 - added copy methods, simplified access through the array
- v1.3 - Added separate initialization for BitPackExt and BitPackDyn
- v1.3.1 - Add copy and move constructor for BitPackDyn. Added tools BitFlags8, BitFlags16, BitFlags32

<a id="install"></a>
## Installation
- The library can be found under the name **BitPack** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/BitPack/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
