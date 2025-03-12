#include <unordered_map>

#include "opCode.h"

std::unordered_map<b1, opCode> codeMap =
{
    // BRK
    {0x00, {0x00, BRK, IMPLIED, 1, 7}},

    // INX
    {0xE8, {0xE8, INX, IMPLIED, 1, 2}},

    // LDA
    {0xA9, {0xA9, LDA, IMMEDIATE, 2, 2}},
    {0xA5, {0xA5, LDA, ZERO_PAGE, 2, 3}},
    {0xB5, {0xB5, LDA, ZERO_PAGE_X, 2, 4}},
    {0xAD, {0xAD, LDA, ABSOLUTE, 3, 4}},
    {0xBD, {0xBD, LDA, ABSOLUTE_X, 3, 4}},
    {0xB9, {0xB9, LDA, ABSOLUTE_Y, 3, 4}},
    {0xA1, {0xA1, LDA, INDIRECT_X, 2, 6}},
    {0xB1, {0xB1, LDA, INDIRECT_Y, 2, 5}},

    // TAX
    {0xAA, {0xAA, TAX, IMPLIED, 1, 2}},

};

const opCode& lookupCode(b1 b)
{
    auto iter = codeMap.find(b);
    if(iter == codeMap.end())
    {
        printf("Couldn't lookup bytecode %X\nReturning BRK", b);
        return codeMap.at(0x00);
    }
    return iter->second;
}

std::string instrStr(const instruction instr)
{
    switch(instr)
    {
        case LDA:
            return "LDA";
        case BRK:
            return "BRK";
        case TAX:
            return "TAX";
        case INX:
            return "INX";
        default:
            return "UNKNOWN_INSTRUCTION";
        }
}

std::string addrStr(const addressMode mode)
{
    switch(mode)
    {
        case IMPLIED:
            return "IMPLIED";
        case IMMEDIATE:
            return "IMMEDIATE";
        case ZERO_PAGE:
            return "ZERO_PAGE";
        case ZERO_PAGE_X:
            return "ZERO_PAGE_X";
        case ABSOLUTE:
            return "ABSOLUTE";
        case ABSOLUTE_X:
            return "ABSOLUTE_X";
        case ABSOLUTE_Y:
            return "ABSOLUTE_Y";
        case INDIRECT:
            return "INDIRECT";
        case INDIRECT_X:
            return "INDIRECT_X";
        case INDIRECT_Y:
            return "INDIRECT_Y";
        default:
            return "UNKNOWN_ADDRESS_MODE";
    }
}

void print(const opCode& c)
{
    printf("CODE: %X, INSTR: %s, ADDR_MODE: %s\n", c.code, instrStr(c.instr).c_str(), addrStr(c.addrMode).c_str());
}
