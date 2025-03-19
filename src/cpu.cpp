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
        case AND:
            return _and(code);
        case LDA:
            return lda(code);
        case TAX:
            return tax(code);
        case INX:
            return inx(code);
        case STA:
            return sta(code);
        case STX:
            return stx(code);
        case STY:
            return sty(code);
        case BRK:
            return brk(code);
        default:
            printf("Couldn't find case for code!");
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

void CPU::_and(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 mask = m_mem.read1(loc);

    m_regA &= mask;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::lda(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    printf("lda addr: %X", loc);
    m_regA = m_mem.read1(loc);
    printf("regA : %X", m_regA);

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
    m_pc = m_mem.read2(Memory::BRK_ADDR);

    printf("m_pc: %X, BRK_ADDR: %X\n", m_pc, Memory::BRK_ADDR);
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
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regA);
}

void CPU::stx(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regX);
}

void CPU::sty(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regY);
}

b2 CPU::getAddr(addressMode mode)
{
    b2 fb = static_cast<b2>(eat());
    switch(mode)
    {
        case IMMEDIATE:
            return m_pc - 1;
        case ZERO_PAGE:
            return fb;
        case ZERO_PAGE_X:
            return fb + m_regX;
        case ZERO_PAGE_Y:
            return fb + m_regY;
        case ABSOLUTE:
            return (fb << 8) | eat();
        case ABSOLUTE_X:
            return (fb << 8) | (eat() + m_regX);
        case ABSOLUTE_Y:
            return (fb << 8) | (eat() + m_regY);
        //TODO wrong?
        case INDIRECT:
            return (fb << 8) | eat();
        case INDIRECT_X:
            {
                b1 zpAddr = fb + m_regX;
                b2 lo = m_mem.read1(zpAddr);
                b2 hi = m_mem.read1(b1(zpAddr + 1));
                return (hi << 8) | lo;
            }
        case INDIRECT_Y:
            {
                b1 zpAddr = fb;
                b2 lo = m_mem.read1(zpAddr);
                b2 hi = m_mem.read1(b1(zpAddr + 1));
                b2 addr = ((hi << 8) | lo);
                return ((hi << 8) | lo) + m_regY;
            }
    }
}

b1 CPU::getA()
{
    return m_regA;
}

b1 CPU::getX()
{
    return m_regX;
}

b1 CPU::getY()
{
    return m_regY;
}

b1 CPU::getStatus()
{
    return m_status;
}

b2 CPU::getPC()
{
    return m_pc;
}

void CPU::setA(b1 v)
{
    m_regA = v;
}

void CPU::setX(b1 v)
{
    m_regX = v;
}

void CPU::setY(b1 v)
{
    m_regY = v;
}

void CPU::setStatus(b1 v)
{
    m_status = v;
}

void CPU::setPC(b2 v)
{
    m_pc = v;
}
