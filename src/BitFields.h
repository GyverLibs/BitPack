#pragma once
#include <inttypes.h>

// ================= BIT FIELDS =================

inline constexpr uint32_t bitfGet(uint32_t value, uint32_t mask) {
    return mask ? (value & mask) >> __builtin_ctzl(mask) : 0;
}

inline constexpr uint32_t bitfMake(uint32_t field, uint32_t mask) {
    return mask ? (field << __builtin_ctzl(mask)) & mask : 0;
}

inline constexpr uint32_t bitfSet(uint32_t value, uint32_t field, uint32_t mask) {
    return mask ? (value & ~mask) | bitfMake(field, mask) : value;
}
