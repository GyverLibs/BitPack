/*
    BitPack - библиотека для упаковки битовых флагов в байтовый массив (экономия места)
    Документация:
    GitHub: https://github.com/GyverLibs/BitPack

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
*/

#pragma once
#include <Arduino.h>

#define BP_BYTE(pack, idx) pack[(idx) >> 3]
#define BP_BIT(pack, idx) ((idx) & 0b111)
#define BP_SET(pack, idx) (BP_BYTE(pack, idx) |= 1 << BP_BIT(pack, idx))
#define BP_CLEAR(pack, idx) (BP_BYTE(pack, idx) &= ~(1 << BP_BIT(pack, idx)))
#define BP_READ(pack, idx) ((BP_BYTE(pack, idx) >> BP_BIT(pack, idx)) & 1)
#define BP_TOGGLE(pack, idx) (BP_BYTE(pack, idx) ^= 1 << BP_BIT(pack, idx))
#define BP_WRITE(pack, idx, val) (val) ? BP_SET(pack, idx) : BP_CLEAR(pack, idx)

// ============== STATIC PACK ==============
template <uint16_t AMOUNT>
class BitPack {
   public:
    uint8_t pack[(AMOUNT + 8 - 1) >> 3];  // round up

    BitPack() {
        clearAll();
    }

    // размер pack в байтах
    uint16_t size() {
        return (AMOUNT + 8 - 1) >> 3;
    }

    // количество флагов
    uint16_t amount() {
        return AMOUNT;
    }

    // установить
    void set(uint16_t idx) {
        if (idx < AMOUNT) BP_SET(pack, idx);
    }

    // снять
    void clear(uint16_t idx) {
        if (idx < AMOUNT) BP_CLEAR(pack, idx);
    }

    // инвертировать
    void toggle(uint16_t idx) {
        if (idx < AMOUNT) BP_TOGGLE(pack, idx);
    }

    // записать
    void write(uint16_t idx, bool state) {
        if (idx < AMOUNT) BP_WRITE(pack, idx, state);
    }

    // прочитать
    bool read(uint16_t idx) {
        if (idx < AMOUNT) return BP_READ(pack, idx);
        else return 0;
    }

    // установить все
    void setAll() {
        memset(pack, 255, size());
    }

    // очистить все
    void clearAll() {
        memset(pack, 0, size());
    }

#ifndef BP_NO_ARRAY
    BitPack& operator[](uint16_t idx) {
        _idx = idx;
        return *this;
    }
    void operator=(bool val) {
        write(_idx, val);
    }
    operator bool() {
        return read(_idx);
    }
#endif

   private:
#ifndef BP_NO_ARRAY
    uint16_t _idx;
#endif
};

// ============== EXTERNAL BUFFER ==============
class BitPackExt {
   public:
    uint8_t* pack;

    // передать буфер и его размер в количестве флагов (8 флагов - 1 байт)
    BitPackExt(uint8_t* pack, uint16_t amount, bool clear = true) : pack(pack), _amount(amount) {
        if (clear) clearAll();
    }

    // размер pack в байтах
    uint16_t size() {
        return (_amount + 8 - 1) >> 3;  // round up
    }

    // количество флагов
    uint16_t amount() {
        return _amount;
    }

    // установить
    void set(uint16_t idx) {
        if (idx < _amount) BP_SET(pack, idx);
    }

    // снять
    void clear(uint16_t idx) {
        if (idx < _amount) BP_CLEAR(pack, idx);
    }

    // инвертировать
    void toggle(uint16_t idx) {
        if (idx < _amount) BP_TOGGLE(pack, idx);
    }

    // записать
    void write(uint16_t idx, bool state) {
        if (idx < _amount) BP_WRITE(pack, idx, state);
    }

    // прочитать
    bool read(uint16_t idx) {
        if (idx < _amount) return BP_READ(pack, idx);
        else return 0;
    }

    // установить все
    void setAll() {
        memset(pack, 255, size());
    }

    // очистить все
    void clearAll() {
        memset(pack, 0, size());
    }

#ifndef BP_NO_ARRAY
    BitPackExt& operator[](uint16_t idx) {
        _idx = idx;
        return *this;
    }
    void operator=(bool val) {
        write(_idx, val);
    }
    operator bool() {
        return read(_idx);
    }
#endif

   protected:
    uint16_t _amount;

   private:
#ifndef BP_NO_ARRAY
    uint16_t _idx;
#endif
};

// ============== DYNAMIC BUFFER ==============
class BitPackDyn : public BitPackExt {
   public:
    // указать количество флагов
    BitPackDyn(uint16_t amount) : BitPackExt(nullptr, amount) {
        pack = (uint8_t*)malloc(size());
        if (!pack) this->_amount = 0;
    }

    ~BitPackDyn() {
        if (pack) free(pack);
    }

   private:
};