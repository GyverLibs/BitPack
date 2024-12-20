#pragma once
#include <inttypes.h>

// ================= BIT FLAGS =================
template <typename T>
struct BitFlags {
    // пакет флагов
    T flags = 0;

    // прочитать бит
    template <typename T1>
    inline bool read(const T1 x) const {
        return flags & (T)x;
    }

    // установить биты маской
    template <typename T1>
    inline void set(const T1 x) {
        flags |= (T)x;
    }

    // очистить биты маской
    template <typename T1>
    inline void clear(const T1 x) {
        flags &= ~((T)x);
    }

    // записать бит
    template <typename T1>
    inline void write(const T1 x, const bool v) {
        v ? set(x) : clear(x);
    }

    // получить маску
    template <typename T1>
    inline T mask(const T1 x) const {
        return flags & (T)x;
    }

    // стоят все биты в маске
    template <typename T1>
    inline bool isSet(const T1 x) const {
        return (flags & (T)x) == (T)x;
    }

    // очищены все биты в маске
    template <typename T1>
    inline bool isClear(const T1 x) const {
        return !(flags & (T)x);
    }

    // сравнить маску со значением
    template <typename T1, typename T2>
    inline bool compare(const T1 x, const T2 y) const {
        return (flags & (T)x) == (T)y;
    }
};

struct BitFlags8 : public BitFlags<uint8_t> {};
struct BitFlags16 : public BitFlags<uint16_t> {};
struct BitFlags32 : public BitFlags<uint32_t> {};