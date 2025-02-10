// cpu.cpp
#pragma once

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
        INDIRECT,
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


private:
    b1 get();
    b1 eat();
    b2 getAddr(addressMode mode);
    void evaluate();

    void setStatusBit(statusBit bit, bool set);

    void lda();
    void brk();
    void tax();

    bool m_run;


    Memory& m_mem;
    b1 m_status;
    b2 m_pc;
    b1 m_regA;
    b1 m_regX;
    b1 m_regY;
};
