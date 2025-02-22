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
        PROG_START = 0x8000,
        ROM_END = 0xFFFF,
    };

    b1 read1(b2 loc);
    void write1(b2 loc, b1 val);
    b2 read2(b2 loc);
    void write2(b2 loc, b2 val);
    void load(const std::vector<b1>& prog);

    void printProgramMemory(b2 numBytes);

private:
    std::array<b1, 0xFFFF> m_data;
};
