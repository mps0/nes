// memory.cpp
#include <algorithm>
#include <cassert>
#include <cstdio>

#include "memory.h"

b1 Memory::read1(b2 loc)
{
    assert(loc < m_data.size());

    //printf("reading: %d", loc);
    return m_data[loc];
}

void Memory::write1(b2 loc, b1 val)
{
    assert(loc < m_data.size());

    m_data[loc] = val;
}

b2 Memory::read2(b2 loc)
{
    assert(loc + 1 < static_cast<b2>(m_data.size()));

    b2 lo = read1(loc);
    b2 hi = read1(loc + 1);

    return (hi << 8) | lo;
}

void Memory::write2(b2 loc, b2 val)
{
    assert(loc + 1 < static_cast<b2>(m_data.size()));

    write1(loc, val);
    write1(loc + 1, val >> 8);
}

void Memory::load(const std::vector<b1>& prog)
{
    assert(prog.size() <= ROM_END - PROG_START + 1);
    std::copy_n(prog.begin(), prog.size(), m_data.begin() + PROG_START);
}

void Memory::printProgramMemory(b2 numBytes)
{
    printf("Printing memory!\n");
    b2 loc = PROG_START;
    b2 end = PROG_START + numBytes;

    getchar();
    while(loc < end)
    {
        printf("LOC: %X, VALUE: %X\n", loc, m_data[loc]);
        ++loc;
    }
}
