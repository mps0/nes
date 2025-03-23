#pragma once

#include <cstdint>

#define sign8(X) *reinterpret_cast<int8_t*>(&X)
#define usign8(X) *reinterpret_cast<uint8_t*>(&X)

using b1 = uint8_t;
using sb1 = int8_t;
using b2 = uint16_t;
using sb2 = int16_t;

constexpr uint8_t nBit1 = 1u << 7u;
constexpr uint16_t nBit2 = 1u << 15u;

inline bool negBitSet(b1 b)
{
    return nBit1 & b;
}

inline bool negBitSet(b2 b)
{
    return nBit2 & b;
}

inline b2 toLittleEndian(b2 b)
{
    b2 lo = b & 0xFF;
    b2 hi = b & 0xFF00;

    return (lo << 8) | (hi  >> 8);
}
