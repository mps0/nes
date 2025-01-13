// cpu.cpp
#pragma once

#include <functional>
#include <set>

#include "byte.h"
#include "memory.h"

class CPU
{
public:
    enum addressMode : uint8_t
    {
        IMMEDIATE,
        ZERO_PAGE,
        ZERO_PAGE_X,
        ABSOLUTE,
        ABSOLUTE_X,
        ABSOLUTE_Y,
        INDIRECT_X,
        INDIRECT_Y,
    };

    enum statusBit : uint8_t
    {
        CARRY_FLAG = 1 << 0,
        ZERO_FLAG = 1 << 1,
        INTERUPT_DISABLE = 1 << 2,
        DECIMAL_MODE_FLAG = 1 << 3,
        BREAK_COMMND = 1 << 4,
        OVERFLOW_FLAG = 1 << 5,
        NEGATIVE_FLAG = 1 << 6
    };

public:

    enum opcode : b1
    {
        LDA = 0xA9,
        BRK = 0x00,
        TAX = 0xAA,
    };
    CPU(Memory& mem);

    void run();
    void reset();

    void getInst(b1 val);

    b1 A();
    b1 X();
    b2 PC();

    void setA(b1 val);
    void setX(b1 val);
    void setPC(b2 val);
    void incrPC(b2 val);
    void declPC(b2 val);
    void setStatusBit(statusBit bit, bool set);

private:
    b1 get();
    b1 eat();
    void evaluate();

    void lda();
    void brk();
    void tax();

    Memory& m_mem;
    b1 m_status;
    b2 m_pc;
    b1 m_regA;
    b1 m_regX;


};

