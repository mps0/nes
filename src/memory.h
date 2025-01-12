// memory.h
#pragma once

#include "byte.h"
#include <vector>

class Memory
{
public:
    b1 read(b2 loc);
    void write(b2 loc, b1 val);


private:

    enum memOffset : b2
    {
        ROM_STRART = 0x8000,
        ROM_END = 0xFFFF,
    };

    std::vector<b1> m_data;
};

