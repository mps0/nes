// memory.cpp
#include <algorithm>
#include <cassert>

#include "memory.h"

b1 Memory::read1(b2 loc)
{
    assert(loc < m_data.size());

    return m_data[loc];
}

void Memory::write1(b2 loc, b1 val)
{
    assert(loc < m_data.size());

    m_data[loc] = val;
}

b2 Memory::read2(b2 loc)
{
    assert(loc + 1 < m_data.size());

    b2 lo = read1(loc);
    b2 hi = read1(loc + 1);

    return (hi << 8) | lo;
}

void Memory::write2(b2 loc, b2 val)
{
    assert(loc + 1 < m_data.size());

    write1(loc, val);
    write1(loc + 1, val >> 8);
}

void Memory::load(const std::vector<b1>& prog)
{
    assert(prog.size() <= ROM_END - ROM_START + 1);
    std::copy_n(prog.begin(), prog.size(), m_data.begin());
}
