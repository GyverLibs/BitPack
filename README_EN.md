This is an automatic translation, may be incorrect in some places. See sources and examples!

# Bitpack
Library for packing bit flags in the byte array (saving space) for Arduino

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id="init"> </a>
## initialization

`` `CPP
// indicate the number of flags
Bitpack <10> Pack;// static buffer inside
Bitpackdyn Pack (10);// Dynamic discharge

uint8_t buf [2];// 1 byte - 8 flags
Bitpackext Pack (BUF, 10);// 10 flags
`` `

<a id="usage"> </a>
## Usage

`` `CPP
// Methods
VOID set (uint8_t num);// install
Void Clear (Uint8_t Num);// reset
VOID TOGGLE (UINT8_T NUM);// switch
VOID Write (Uint8_t Num, Bool State);// Record
Bool Read (uint8_t num);// Read
VOID setall ();// install everything
VOID CLEARALL ();// throw everything
uint16_t amount ();// number of flags
uint16_t size ();// Pack size in bytes

uint8_t* pack;// access to the buffer

// Macro
BP_SET (PACK, IDX)
BP_Clear (Pack, IDX)
Bp_read (Pack, IDX)
BP_TOGGLE (PACK, IDX)
BP_WRITE (PACK, IDX)

// Settings (before connecting the library)
#define bp_no_arry // Remove access through [] - saves 2 bytes RAM
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!

`` `CPP
#include "Bitpack.h"

// indicate the number of flags
Bitpack <10> Flags;

VOID setup () {
  Serial.Begin (9600);
  Flags.clerall ();// lower everything
  Flags.Set (1);// raise the flag
  Flags.Set (3);
  Flags.write (3, 1);
  Serial.println (Flags.read (0));// Read the flag
  Serial.println (Flags.read (1));
  Serial.println (Flags.read (2));

  Flags [3] = 0;// can be written through []
  Serial.println (Flags [3]);// can be read through []
}

VOID loop () {
}
`` `

<a id="versions"> </a>

## versions
- V1.0
- v1.1 - access for [], new tools have been added
- V1.1.1 - REB

<a id="install"> </a>
## Installation
- The library can be found by the name ** bitpack ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/bitpack/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- Through the IDE library manager:Find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code