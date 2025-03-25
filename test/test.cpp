
#include "../src/cpu.h"
#include "../src/memory.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>

TEST_CASE("ADDRESS MODES")
{
    Memory mem;
    CPU cpu(mem);

    SUBCASE("IMMEDIATE")
    {
        // LDA
        std::vector<b1> program = {0xA9, 0xB7};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xB7);
    }

    SUBCASE("ZERO PAGE")
    {
        // LDA
        std::vector<b1> program = {0xA5, 0x00};

        mem.write1(0x00, 0xA1);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xA1);
    }

    SUBCASE("ZERO PAGE X")
    {
        std::vector<b1> program = {0xB5, 0x0F};

        cpu.setX(0xA1);

        mem.write1(0x0F + cpu.getX(), 0xAA);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xAA);
    }

    SUBCASE("ABSOLUTE")
    {
        std::vector<b1> program = {0xAD, 0x0F, 0x12};

        mem.write1(0x0F12, 0xD6);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xD6);
    }

    SUBCASE("ABSOLUTE X")
    {
        std::vector<b1> program = {0xBD, 0x0F, 0x12};

        cpu.setX(0xA1);

        mem.write1(0x0F12 + cpu.getX(), 0xD6);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xD6);
    }

    SUBCASE("ABSOLUTE Y")
    {
        std::vector<b1> program = {0xB9, 0x0F, 0x12};

        cpu.setY(0xA1);
        mem.write1(0x0F12 + cpu.getY(), 0x12);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0x12);
    }

    SUBCASE("INDIRECT X")
    {
        std::vector<b1> program = {0xA1, 0x10};

        // full address
        b2 addr = 0xAF52;
        mem.write1(addr, 0xA2);

        // zero page
        b1 zpAddrLo = 0x13;
        b1 zpAddrHi = zpAddrLo + 1;
        mem.write1(zpAddrLo, 0x52);
        mem.write1(zpAddrHi, 0xAF);

        cpu.setX(0x03);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xA2);
    }

    SUBCASE("INDIRECT Y")
    {
        std::vector<b1> program = {0xB1, 0xFF};

        cpu.setY(0x2B);
        // full address
        b2 addr = 0xAF52 + cpu.getY();
        mem.write1(addr, 0xA2);

        // zero page
        b1 zpAddrLo = 0xFF;
        b1 zpAddrHi = zpAddrLo + 1;
        mem.write1(zpAddrLo, 0x52);
        mem.write1(zpAddrHi, 0xAF);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xA2);
    }
}

TEST_CASE("OPCodes")
{
    Memory mem;
    CPU cpu(mem);

    SUBCASE("AND")
    {
        std::vector<b1> program = {0x29, 0x2F};

        cpu.setA(0xB7);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == (0xB7 & 0x2F));
    }

    SUBCASE("ASL-accumlator")
    {
        std::vector<b1> program = {0x0A};

        cpu.setA(0x01);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == (0x02));
    }

    SUBCASE("ASL-Absolute")
    {
        std::vector<b1> program = {0x0E, 0x0F, 0x11};

        mem.write1(0x0F11, 0x22);

        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0x0F11) == (0x22 << 1));
    }

    SUBCASE("BRK")
    {
        std::vector<b1> program = {0x00};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == Memory::PROG_START);
        CHECK((cpu.getStatus() & CPU::BREAK_COMMND) > 0);
    }

    SUBCASE("STA")
    {
        std::vector<b1> program = {0x8D, 0x01, 0x42};

        cpu.setA(0xFF);
        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0x0142) == cpu.getA());
    }

    SUBCASE("STX")
    {
        std::vector<b1> program = {0x96, 0xE2};

        cpu.setX(0xF1);
        cpu.setY(0x02);
        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0xE2 + cpu.getY()) == cpu.getX());
    }

    SUBCASE("STY")
    {
        std::vector<b1> program = {0x8C, 0xE2, 0xFF};

        cpu.setY(0x02);
        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0xE2FF) == cpu.getY());
    }

    SUBCASE("TAX")
    {
        std::vector<b1> program = {0xAA};

        cpu.setA(0xB2);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == cpu.getA());
    }

    SUBCASE("TAY")
    {
        std::vector<b1> program = {0xA8};

        cpu.setA(0xB2);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getY() == cpu.getA());
    }

    SUBCASE("TSX")
    {
        std::vector<b1> program = {0xBA};

        cpu.setSP(0x03);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == cpu.getSP());
    }

    SUBCASE("TXA")
    {
        std::vector<b1> program = {0x8A};

        cpu.setX(0x03);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == cpu.getX());
    }

    SUBCASE("TXS")
    {
        std::vector<b1> program = {0x9A};

        cpu.setX(0x03);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getSP() == cpu.getX());
    }

    SUBCASE("TYA")
    {
        std::vector<b1> program = {0x98};

        cpu.setY(0x03);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == cpu.getY());
    }

    SUBCASE("BCC")
    {
        std::vector<b1> program = {0x90, 0x31};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BCS")
    {
        std::vector<b1> program = {0xB0, 0x31};

        cpu.setStatus(CPU::CARRY_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BEQ")
    {
        std::vector<b1> program = {0xF0, 0x31};

        cpu.setStatus(CPU::ZERO_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BIT")
    {
        std::vector<b1> program = {0x24, 0x31};

        cpu.setA(0xFF);
        mem.write1(0x31, 0x40);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.isStatusBitSet(CPU::OVERFLOW_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::NEGATIVE_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::ZERO_FLAG));
    }

    SUBCASE("BMI")
    {
        std::vector<b1> program = {0x30, 0x31};

        cpu.setStatus(CPU::NEGATIVE_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BMI")
    {
        std::vector<b1> program = {0xD0, 0x31};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BPL")
    {
        std::vector<b1> program = {0x10, 0x31};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BVC")
    {
        std::vector<b1> program = {0x50, 0x31};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("BVS")
    {
        std::vector<b1> program = {0x70, 0x31};

        cpu.setStatus(CPU::OVERFLOW_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == (Memory::PROG_START + 0x31 + 2));
    }

    SUBCASE("CLC")
    {
        std::vector<b1> program = {0x18};

        cpu.setStatus(CPU::CARRY_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(!cpu.isStatusBitSet(CPU::CARRY_FLAG));
    }

    SUBCASE("CLD")
    {
        std::vector<b1> program = {0xD8};

        cpu.setStatus(CPU::DECIMAL_MODE_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(!cpu.isStatusBitSet(CPU::DECIMAL_MODE_FLAG));
    }

    SUBCASE("CLI")
    {
        std::vector<b1> program = {0x58};

        cpu.setStatus(CPU::INTERUPT_DISABLE_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(!cpu.isStatusBitSet(CPU::INTERUPT_DISABLE_FLAG));
    }

    SUBCASE("CLV")
    {
        std::vector<b1> program = {0xB8};

        cpu.setStatus(CPU::OVERFLOW_FLAG);
        mem.load(program);
        cpu.run(1);

        CHECK(!cpu.isStatusBitSet(CPU::OVERFLOW_FLAG));
    }

    SUBCASE("CMP")
    {
        std::vector<b1> program = {0xC9, 0x0F};

        cpu.setA(0xFF);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.isStatusBitSet(CPU::CARRY_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::ZERO_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::NEGATIVE_FLAG));
    }

    SUBCASE("CPX")
    {
        std::vector<b1> program = {0xE0, 0x0F};

        cpu.setX(0xFF);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.isStatusBitSet(CPU::CARRY_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::ZERO_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::NEGATIVE_FLAG));
    }

    SUBCASE("CPY")
    {
        std::vector<b1> program = {0xC0, 0x0F};

        cpu.setY(0xFF);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.isStatusBitSet(CPU::CARRY_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::ZERO_FLAG));
        CHECK(!cpu.isStatusBitSet(CPU::NEGATIVE_FLAG));
    }

    SUBCASE("DEC")
    {
        std::vector<b1> program = {0xD6, 0x01};

        mem.write1(0x0F, 0x0A);
        cpu.setX(0x0E);
        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0x0F) == 0x09);
    }

    SUBCASE("DEX")
    {
        std::vector<b1> program = {0xCA};

        cpu.setX(0x0E);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == 0x0D);
    }

    SUBCASE("DEY")
    {
        std::vector<b1> program = {0x88};

        cpu.setY(0x0E);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getY() == 0x0D);
    }

    SUBCASE("EOR")
    {
        std::vector<b1> program = {0x49, 0x0F};

        cpu.setA(0x03);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0x0C);
    }

    SUBCASE("INC")
    {
        std::vector<b1> program = {0xE6, 0x10};

        mem.write1(0x10, 0x02);

        mem.load(program);
        cpu.run(1);

        CHECK(mem.read1(0x10) == 0x03);
    }

    SUBCASE("INX")
    {
        std::vector<b1> program = {0xE8};

        cpu.setX(1);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == 2);
    }

    SUBCASE("INY")
    {
        std::vector<b1> program = {0xC8};

        cpu.setY(1);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getY() == 2);
    }

    SUBCASE("JMP")
    {
        std::vector<b1> program = {0x6C, 0x01, 0xFF};

        mem.write2(0x01FF, 0xAAAA);
        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getPC() == 0xAAAA);
    }

    SUBCASE("LDA")
    {
        std::vector<b1> program = {0xA9, 0xB7};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xB7);
    }

    SUBCASE("LDX")
    {
        std::vector<b1> program = {0xA2, 0xB7};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == 0xB7);
    }

    SUBCASE("LDY")
    {
        std::vector<b1> program = {0xA0, 0xB7};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getY() == 0xB7);
    }
}
