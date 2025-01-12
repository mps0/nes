// cpu.cpp
#pragma once

#include "byte.h"
#include "memory.h"

class CPU
{
private:
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

    enum opcode : b1
    {
        LDA = 0xA9,
        BRK = 0x00,
        TAX = 0xAA,
    };

public:
    CPU(Memory& mem);

    void run();

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

    void setStatusBit(statusBit bit, bool set);

};
