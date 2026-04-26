#pragma once
#include <inttypes.h>

// ================= BIT FIELDS =================

inline constexpr uint32_t bitfGet(uint32_t value, uint32_t mask) {
    return (value & mask) >> __builtin_ctzl(mask);
}

inline constexpr uint32_t bitfMake(uint32_t field, uint32_t mask) {
    return (field << __builtin_ctzl(mask)) & mask;
}

inline constexpr uint32_t bitfSet(uint32_t value, uint32_t field, uint32_t mask) {
    return (value & ~mask) | bitfMake(field, mask);
}