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

    b1 getA();
    b1 getX();
    b1 getY();
    b1 getSP();
    b1 getStatus();
    b2 getPC();

    void setA(b1 v);
    void setX(b1 v);
    void setY(b1 v);
    void setSP(b1 v);
    void setStatus(b1 v);
    void setPC(b2 v);

private:
    b1 get();
    b1 eat();
    b2 getAddr(addressMode mode);
    void evaluate();

    void setStatusBit(statusBit bit, bool set);

    void _and(const opCode& code);
    void asl(const opCode& code);
    void brk(const opCode& code);
    void inx(const opCode& code);
    void lda(const opCode& code);
    void sta(const opCode& code);
    void stx(const opCode& code);
    void sty(const opCode& code);
    void tax(const opCode& code);
    void tay(const opCode& code);
    void tsx(const opCode& code);
    void txa(const opCode& code);
    void txs(const opCode& code);
    void tya(const opCode& code);

    bool m_run;

    Memory& m_mem;
    b2 m_pc;
    b1 m_sp;
    b1 m_status;
    b1 m_regA;
    b1 m_regX;
    b1 m_regY;
};
