// cpu.cpp
#pragma once

#include "byte.h"
#include "memory.h"
#include "opCode.h"

class CPU
{
public:
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

    void brk(const opCode& code);
    void lda(const opCode& code);
    void inx(const opCode& code);
    void tax(const opCode& code);
    void sta(const opCode& code);

    bool m_run;


    Memory& m_mem;
    b1 m_status;
    b2 m_pc;
    b1 m_regA;
    b1 m_regX;
    b1 m_regY;
};
