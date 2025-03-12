// cpu.cpp

#include "cpu.h"
#include <cstdio>
#include <iostream>

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
    m_run = true;
}
void CPU::run()
{
    reset();

    while(m_run)
    {
        evaluate();
    }
}

void CPU::evaluate()
{
    const opCode& code = lookupCode(eat());
    print(code);

    switch(code.instr)
    {
        case LDA:
            return lda(code);
        case TAX:
            return tax(code);
        case INX:
            return inx(code);
        case BRK:
        default:
            return brk(code);
    };
}

b1 CPU::eat()
{
    b1 k = m_mem.read1(m_pc++);
    return k;
}

b1 CPU::get()
{
    return m_mem.read1(m_pc);
}

void CPU::setStatusBit(statusBit bit, bool set)
{
    if(set)
        m_status |= bit;
    else
        m_status &= ~bit;
}

void CPU::lda(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_regA = m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::inx(const opCode& code)
{
    m_regX = m_regX + 1;

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::brk(const opCode& code)
{
    //TODO wrong
    m_pc = toLittleEndian(0xFFFE);

    setStatusBit(BREAK_COMMND, true);
    m_run = false;
}

void CPU::tax(const opCode& code)
{
    m_regX = m_regA;

    setStatusBit(ZERO_FLAG, m_regX == 0);
}

void CPU::sta(const opCode& code)
{

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
            return (fb << 8) | (eat() + m_regX);
        case ABSOLUTE_Y:
            return (fb << 8) | (eat() + m_regY);
        case INDIRECT:
            return (fb << 8) | eat();
        case INDIRECT_X:
            return (fb << 8) + m_regX;
        case INDIRECT_Y:
            return (fb << 8) + m_regY;
            break;
    }
}
