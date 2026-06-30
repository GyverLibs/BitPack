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
#include "BitFlags.h"

#define BP_BYTE(pack, idx) pack[(idx) >> 3]
#define BP_BIT(pack, idx) ((idx) & 0b111)
#define BP_SET(pack, idx) (BP_BYTE(pack, idx) |= 1 << BP_BIT(pack, idx))
#define BP_CLEAR(pack, idx) (BP_BYTE(pack, idx) &= ~(1 << BP_BIT(pack, idx)))
#define BP_READ(pack, idx) ((BP_BYTE(pack, idx) >> BP_BIT(pack, idx)) & 1)
#define BP_TOGGLE(pack, idx) (BP_BYTE(pack, idx) ^= 1 << BP_BIT(pack, idx))
#define BP_WRITE(pack, idx, val) ((val) ? BP_SET(pack, idx) : BP_CLEAR(pack, idx))

// ============== COMMON PACK API ==============
template <typename T>
class BitPackBase {
   public:
    // размер pack в байтах
    uint16_t size() const {
        uint16_t amount = _self().amount();
        return (amount >> 3) + !!(amount & 0b111);
    }

    // установить
    void set(uint16_t idx) {
        if (_data() && idx < _self().amount()) BP_SET(_data(), idx);
    }

    // снять
    void clear(uint16_t idx) {
        if (_data() && idx < _self().amount()) BP_CLEAR(_data(), idx);
    }

    // инвертировать
    void toggle(uint16_t idx) {
        if (_data() && idx < _self().amount()) BP_TOGGLE(_data(), idx);
    }

    // записать
    void write(uint16_t idx, bool state) {
        if (_data() && idx < _self().amount()) BP_WRITE(_data(), idx, state);
    }

    // прочитать
    bool read(uint16_t idx) const {
        if (_data() && idx < _self().amount()) return BP_READ(_data(), idx);
        else return 0;
    }

    // установить все
    void setAll() {
        if (_data()) memset(_data(), 255, size());
    }

    // очистить все
    void clearAll() {
        if (_data()) memset(_data(), 0, size());
    }

    // копировать в
    template <typename T1>
    bool copyTo(T1& bp) const {
        if (!_data() || !bp.pack || _self().amount() != bp.amount()) return 0;
        memcpy(bp.pack, _data(), size());
        return 1;
    }

    // копировать из
    template <typename T1>
    bool copyFrom(const T1& bp) {
        if (!_data() || !bp.pack || _self().amount() != bp.amount()) return 0;
        memcpy(_data(), bp.pack, size());
        return 1;
    }

#ifndef BP_NO_ARRAY
    class BitRef {
       public:
        BitRef(BitPackBase& bp, uint16_t idx) : _bp(bp), _idx(idx) {}

        BitRef& operator=(bool val) {
            _bp.write(_idx, val);
            return *this;
        }
        BitRef& operator=(const BitRef& ref) {
            return *this = bool(ref);
        }
        operator bool() const {
            return _bp.read(_idx);
        }

       private:
        BitPackBase& _bp;
        uint16_t _idx;
    };

    BitRef operator[](uint16_t idx) {
        return BitRef(*this, idx);
    }
    bool operator[](uint16_t idx) const {
        return read(idx);
    }
#endif

   private:
    T& _self() {
        return static_cast<T&>(*this);
    }
    const T& _self() const {
        return static_cast<const T&>(*this);
    }
    uint8_t* _data() {
        return _self().pack;
    }
    const uint8_t* _data() const {
        return _self().pack;
    }
};

// ============== STATIC PACK ==============
template <uint16_t flag_amount>
class BitPack : public BitPackBase<BitPack<flag_amount>> {
   public:
    static_assert(flag_amount > 0, "flag_amount must be greater than 0");

    uint8_t pack[(flag_amount >> 3) + !!(flag_amount & 0b111)];

    BitPack() {
        this->clearAll();
    }

    // количество флагов
    uint16_t amount() const {
        return flag_amount;
    }
};

// ============== EXTERNAL BUFFER ==============
class BitPackExt : public BitPackBase<BitPackExt> {
   public:
    uint8_t* pack = nullptr;

    BitPackExt() : _amount(0) {}

    // передать буфер и его размер в количестве флагов (8 флагов - 1 байт)
    BitPackExt(uint8_t* pack, uint16_t amount, bool clear = true) {
        setBuffer(pack, amount, clear);
    }

    // передать буфер и его размер в количестве флагов (8 флагов - 1 байт)
    void setBuffer(uint8_t* pack, uint16_t amount, bool clear = true) {
        this->pack = pack;
        this->_amount = amount;
        if (clear) clearAll();
    }

    // количество флагов
    uint16_t amount() const {
        return _amount;
    }

   protected:
    uint16_t _amount;
};

// ============== DYNAMIC BUFFER ==============
class BitPackDyn : public BitPackExt {
   public:
    BitPackDyn() {}

    // указать количество флагов
    BitPackDyn(uint16_t amount) {
        init(amount);
    }

    BitPackDyn(const BitPackDyn& val) {
        copy(val);
    }
    BitPackDyn& operator=(const BitPackDyn& val) {
        copy(val);
        return *this;
    }

#if __cplusplus >= 201103L
    BitPackDyn(BitPackExt&&) = delete;
    BitPackDyn& operator=(BitPackExt&&) = delete;

    BitPackDyn(BitPackDyn&& rval) noexcept {
        move(rval);
    }
    BitPackDyn& operator=(BitPackDyn&& rval) noexcept {
        move(rval);
        return *this;
    }
#endif

    ~BitPackDyn() {
        delete[] pack;
    }

    // указать количество флагов
    void init(uint16_t amount) {
        delete[] pack;
        pack = nullptr;
        _amount = amount;  // need for size()
        if (!amount) return;
        pack = new uint8_t[size()];
        if (!pack) _amount = 0;
        clearAll();
    }

    // удалить буфер
    void reset() {
        delete[] pack;
        pack = nullptr;
        _amount = 0;
    }

    // копировать из
    void copy(const BitPackDyn& val) {
        if (this == &val) return;
        if (!val.pack) {
            reset();
            return;
        }
        if (!pack || _amount != val._amount) init(val._amount);
        if (!pack) return;
        memcpy(pack, val.pack, val.size());
    }

    // переместить из
    void move(BitPackDyn& rval) noexcept {
        if (this == &rval) return;
        delete[] pack;
        pack = rval.pack;
        _amount = rval._amount;
        rval.pack = nullptr;
        rval._amount = 0;
    }
};
