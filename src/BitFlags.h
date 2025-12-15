#pragma once
#include <inttypes.h>

// ================= BIT FLAGS =================
template <typename T>
struct BitFlags {
    // пакет флагов
    T flags{};

    // установить биты маской
    template <typename T1>
    inline void set(const T1 mask) {
        flags |= T(mask);
    }

    // очистить биты маской
    template <typename T1>
    inline void clear(const T1 mask) {
        flags &= ~T(mask);
    }

    // записать биты маской
    template <typename T1>
    inline void write(const T1 mask, const bool val) {
        val ? set(mask) : clear(mask);
    }

    // записать биты по маске
    template <typename T1, typename T2>
    inline void writeBits(const T1 mask, const T2 bits) {
        flags = (flags & ~T(mask)) | (T(bits) & T(mask));
    }

    // прочитать маской
    template <typename T1>
    inline T read(const T1 mask) const {
        return flags & T(mask);
    }

    // стоят все биты в маске
    template <typename T1>
    inline bool isSet(const T1 mask) const {
        return compare(mask, mask);
    }

    // очищены все биты в маске
    template <typename T1>
    inline bool isClear(const T1 mask) const {
        return read(mask) == 0;
    }

    // сравнить маску со значением
    template <typename T1, typename T2>
    inline bool compare(const T1 mask, const T2 val) const {
        return read(mask) == T(val);
    }
};

struct BitFlags8 : public BitFlags<uint8_t> {};
struct BitFlags16 : public BitFlags<uint16_t> {};
struct BitFlags32 : public BitFlags<uint32_t> {};