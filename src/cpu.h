// cpu.cpp

#include <cstdint>
#include <vector>

using b1 = uint8_t;
using b2 = uint16_t;



enum opcode : b1
{
    LDA = 0xA9,
    BRK = 0x00,
    TAX = 0xAA,

};

class Memory
{
public:
    b1 read(b2 loc);
    void write(b2 loc, b1 val);


private:

    enum memOffset : b2
    {
        ROM_STRART = 0x8000,
        ROM_END = 0xFFFF,

    };

    std::vector<b1> m_data;
};

class CPU
{
private:
    enum statusBit
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

private:
    b1 get();
    b1 eat();
    void evaluate();

    void lda();
    void brk();
    void tax();

    b1 m_status;
    b1 m_regA;
    b1 m_regX;
    b2 m_pc;


    void setStatusBit(statusBit bit, bool set);

    Memory& m_mem;
};
