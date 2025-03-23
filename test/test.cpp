
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

    SUBCASE("LDA")
    {
        std::vector<b1> program = {0xA9, 0xB7};

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getA() == 0xB7);
    }

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

    SUBCASE("INX")
    {
        std::vector<b1> program = {0xE8};

        cpu.setX(1);

        mem.load(program);
        cpu.run(1);

        CHECK(cpu.getX() == 2);
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
}
