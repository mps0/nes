// cpu.cpp

#include "cpu.h"

//
std::

CPU::CPU(Memory& mem) :
    m_mem(mem)
{
    reset();
}

void CPU::reset()
{
    m_status = 0;
    m_regA = 0;
    m_regX = 0;
    m_pc = Memory::PROG_START;
}
void CPU::run()
{
    while(1)
    {
        evaluate();
    }
}

void CPU::evaluate()
{
    switch(eat())
    {
        case LDA:
            return lda();

        case TAX:
            return tax();

        case BRK:
        default:
            return brk();
    };
}

b1 CPU::eat()
{
    return m_mem.read(++m_pc);
}

b1 CPU::get()
{
    return m_mem.read(m_pc);
}

void CPU::setStatusBit(statusBit bit, bool set)
{
    if(set)
        m_status |= bit;
    else
        m_status &= ~bit;
}

void CPU::lda()
{
    b2 loc = getAddr(IMMEDIATE);
    m_regA = m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::brk()
{
    //TODO wrong
    m_pc = toLittleEndian(0xFFFE);

    setStatusBit(BREAK_COMMND, true);
}

void CPU::tax()
{
    m_regX = m_regA;

    setStatusBit(ZERO_FLAG, m_regX == 0);
}

b2 CPU::getAddr(addressMode mode)
{
    b2 fb = eat();
    switch(mode)
    {
        case IMMEDIATE:
            return m_pc - 1;
        case ZERO_PAGE:
            return fb;
        case ZERO_PAGE_X:
            return fb + m_regX;
        case ABSOLUTE:
            return (fb << 8) | eat();
        case ABSOLUTE_X:
            return (fb << 8) | eat() + m_regX;
        case ABSOLUTE_Y:
            return (fb << 8) | eat() + m_regY;
        case INDIRECT:
            return (fb << 8) | eat();
        case INDIRECT_X:
            return (fb << 8) + m_regX;
        case INDIRECT_Y:
            return (fb << 8) + m_regY;
            break;
    }
}
