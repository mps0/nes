// memory.cpp
#include <algorithm>
#include <cassert>

#include "memory.h"

b1 Memory::read(b2 loc)
{
    assert(loc < m_data.size());
    return m_data[loc];
}

void Memory::write(b2 loc, b1 val)
{
    assert(loc < m_data.size());
}

void Memory::load(const std::vector<b1>& prog)
{
    assert(prog.size() <= ROM_END - ROM_START + 1);
    std::copy_n(prog.begin(), prog.size(), m_data.begin());
}
