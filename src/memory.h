// memory.h
#pragma once

#include <array>
#include <vector>

#include "byte.h"

class Memory
{
public:
    enum : b2
    {
        ROM_START = 0x8000,
        ROM_END = 0xFFFF,
        PROG_START = 0xFFFC,
    };

    b1 read(b2 loc);
    void write(b2 loc, b1 val);
    void load(const std::vector<b1>& prog);

private:
    std::array<b1, 0xFFFF> m_data;
};
