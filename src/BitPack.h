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
template <uint16_t flag_amount>
class BitPack {
   public:
    uint8_t pack[(flag_amount + 8 - 1) >> 3];  // round up

    BitPack() {
        clearAll();
    }

    // размер pack в байтах
    uint16_t size() const {
        return (flag_amount + 8 - 1) >> 3;
    }

    // количество флагов
    uint16_t amount() const {
        return flag_amount;
    }

    // установить
    void set(uint16_t idx) {
        if (idx < flag_amount) BP_SET(pack, idx);
    }

    // снять
    void clear(uint16_t idx) {
        if (idx < flag_amount) BP_CLEAR(pack, idx);
    }

    // инвертировать
    void toggle(uint16_t idx) {
        if (idx < flag_amount) BP_TOGGLE(pack, idx);
    }

    // записать
    void write(uint16_t idx, bool state) {
        if (idx < flag_amount) BP_WRITE(pack, idx, state);
    }

    // прочитать
    bool read(uint16_t idx) const {
        if (idx < flag_amount) return BP_READ(pack, idx);
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

    // копировать в
    bool copyTo(BitPack& bp) {
        if (amount() != bp.amount()) return 0;
        memcpy(bp.pack, pack, size());
        return 1;
    }

    // копировать из
    bool copyFrom(BitPack& bp) {
        if (amount() != bp.amount()) return 0;
        memcpy(pack, bp.pack, size());
        return 1;
    }

#ifndef BP_NO_ARRAY
    BitPack& operator[](uint16_t idx) {
        _idx = idx;
        return *this;
    }
    void operator=(bool val) {
        write(_idx, val);
    }
    operator bool() const {
        return read(_idx);
    }
    void operator=(BitPack& bp) {
        write(_idx, (bool)bp);
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
    uint8_t* pack = nullptr;

    BitPackExt() {}

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

    // размер pack в байтах
    uint16_t size() const {
        return (_amount + 8 - 1) >> 3;  // round up
    }

    // количество флагов
    uint16_t amount() const {
        return _amount;
    }

    // установить
    void set(uint16_t idx) {
        if (pack && idx < _amount) BP_SET(pack, idx);
    }

    // снять
    void clear(uint16_t idx) {
        if (pack && idx < _amount) BP_CLEAR(pack, idx);
    }

    // инвертировать
    void toggle(uint16_t idx) {
        if (pack && idx < _amount) BP_TOGGLE(pack, idx);
    }

    // записать
    void write(uint16_t idx, bool state) {
        if (pack && idx < _amount) BP_WRITE(pack, idx, state);
    }

    // прочитать
    bool read(uint16_t idx) const {
        if (pack && idx < _amount) return BP_READ(pack, idx);
        else return 0;
    }

    // установить все
    void setAll() {
        if (pack) memset(pack, 255, size());
    }

    // очистить все
    void clearAll() {
        if (pack) memset(pack, 0, size());
    }

    // копировать в
    bool copyTo(BitPackExt& bp) {
        if (!pack || amount() != bp.amount()) return 0;
        memcpy(bp.pack, pack, size());
        return 1;
    }

    // копировать из
    bool copyFrom(BitPackExt& bp) {
        if (!pack || amount() != bp.amount()) return 0;
        memcpy(pack, bp.pack, size());
        return 1;
    }

#ifndef BP_NO_ARRAY
    BitPackExt& operator[](uint16_t idx) {
        _idx = idx;
        return *this;
    }
    void operator=(bool val) {
        write(_idx, val);
    }
    operator bool() const {
        return read(_idx);
    }
    void operator=(BitPackExt& bp) {
        write(_idx, (bool)bp);
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
    BitPackDyn() {}

    // указать количество флагов
    BitPackDyn(uint16_t amount) {
        init(amount);
    }

    BitPackDyn(const BitPackDyn& val) {
        copy(val);
    }
    void operator=(const BitPackDyn& val) {
        copy(val);
    }

#if __cplusplus >= 201103L
    BitPackDyn(BitPackExt&&) = delete;
    BitPackDyn& operator=(BitPackExt&&) = delete;

    BitPackDyn(BitPackDyn&& rval) noexcept {
        move(rval);
    }
    void operator=(BitPackDyn&& rval) noexcept {
        move(rval);
    }
#endif

    ~BitPackDyn() {
        delete[] pack;
    }

    // указать количество флагов
    void init(uint16_t amount) {
        delete[] pack;
        _amount = amount;  // need for size()
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
        if (this == &val || pack == val.pack) return;
        if (!val.pack) {
            reset();
            return;
        }
        memcpy(pack, val.pack, val.size());
        _amount = val._amount;
    }

    // переместить из
    void move(BitPackDyn& rval) noexcept {
        delete[] pack;
        pack = rval.pack;
        _amount = rval._amount;
        rval.pack = nullptr;
    }
};

// ================= BIT FLAGS =================
template <typename T>
struct BitFlags {
    // пакет флагов
    T flags = 0;

    // прочитать бит
    inline bool read(const T x) const __attribute__((always_inline)) {
        return flags & x;
    }

    // установить биты маской
    inline void set(const T x) __attribute__((always_inline)) {
        flags |= x;
    }

    // очистить биты маской
    inline void clear(const T x) __attribute__((always_inline)) {
        flags &= ~x;
    }

    // записать бит
    inline void write(const T x, const bool v) __attribute__((always_inline)) {
        v ? set(x) : clear(x);
    }

    // получить маску
    inline T mask(const T x) const __attribute__((always_inline)) {
        return flags & x;
    }

    // стоят все биты в маске
    inline bool isSet(const T x) const __attribute__((always_inline)) {
        return (flags & x) == x;
    }

    // очищены все биты в маске
    inline bool isClear(const T x) const __attribute__((always_inline)) {
        return !(flags & x);
    }

    // сравнить маску со значением
    inline bool compare(const T x, const T y) const __attribute__((always_inline)) {
        return (flags & x) == y;
    }
};

struct BitFlags8 : public BitFlags<uint8_t> {};
struct BitFlags16 : public BitFlags<uint16_t> {};
struct BitFlags32 : public BitFlags<uint32_t> {};