#pragma once

#include <cstdint>

#define sign8(X) *reinterpret_cast<int8_t*>(&X)
#define usign8(X) *reinterpret_cast<uint8_t*>(&X)

using b1 = uint8_t;
using b2 = uint16_t;

constexpr uint8_t nBit = 1 << 7;

inline bool negBitSet(b1 b)
{
    return nBit & b;
}

inline b2 toLittleEndian(b2 b)
{
    b2 lo = b & 0xFF;
    b2 hi = b & 0xFF00;

    return (lo << 8) | (hi  >> 8);
}
