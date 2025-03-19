
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
        std::vector<b1> program = {0xA9, 0xB7, 0x00};

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0xB7);
    }

    SUBCASE("ZERO PAGE")
    {
        // LDA
        std::vector<b1> program = {0xA5, 0x00, 0x00};

        mem.write1(0x00, 0xA1);
        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0xA1);
    }

    SUBCASE("ZERO PAGE X")
    {
        std::vector<b1> program = {0xB5, 0x0F, 0x00};

        cpu.setX(0xA1);

        mem.write1(0x0F + cpu.getX(), 0xAA);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0xAA);
    }

    SUBCASE("ABSOLUTE")
    {
        std::vector<b1> program = {0xAD, 0x0F, 0x12, 0x00};

        mem.write1(0x0F12, 0xD6);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0xD6);
    }

    SUBCASE("ABSOLUTE X")
    {
        std::vector<b1> program = {0xBD, 0x0F, 0x12, 0x00};

        cpu.setX(0xA1);

        mem.write1(0x0F12 + cpu.getX(), 0xD6);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0xD6);
    }

    SUBCASE("ABSOLUTE Y")
    {
        std::vector<b1> program = {0xB9, 0x0F, 0x12, 0x00};

        cpu.setY(0xA1);
        mem.write1(0x0F12 + cpu.getY(), 0x12);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == 0x12);
    }

    SUBCASE("INDIRECT X")
    {
        std::vector<b1> program = {0xA1, 0x10, 0x00};

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
        cpu.run();

        CHECK(cpu.getA() == 0xA2);
    }

    SUBCASE("INDIRECT Y")
    {
        std::vector<b1> program = {0xB1, 0xFF, 0x00};

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
        cpu.run();

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
        cpu.run();

        CHECK(cpu.getA() == 0xB7);
    }

    SUBCASE("AND")
    {
        std::vector<b1> program = {0x29, 0x2F};

        cpu.setA(0xB7);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getA() == (0xB7 & 0x2F));
    }

    SUBCASE("INX")
    {
        std::vector<b1> program = {0xE8};

        cpu.setX(1);

        mem.load(program);
        cpu.run();

        CHECK(cpu.getX() == 2);
    }

    SUBCASE("BRK")
    {
        std::vector<b1> program = {0x00};

        mem.load(program);
        cpu.run();

        CHECK(cpu.getPC() == Memory::PROG_START);
        CHECK((cpu.getStatus() & CPU::BREAK_COMMND) > 0);
    }
}
