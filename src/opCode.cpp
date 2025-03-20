#include <unordered_map>

#include "opCode.h"

std::unordered_map<b1, opCode> codeMap =
{
    // AND
    {0x29, {0x29, AND, IMMEDIATE, 2, 2}},
    {0x25, {0x25, AND, ZERO_PAGE, 2, 3}},
    {0x35, {0x35, AND, ZERO_PAGE_X, 2, 4}},
    {0x2D, {0x2D, AND, ABSOLUTE,32, 4}},
    {0x3D, {0x3D, AND, ABSOLUTE_X, 3, 4}},
    {0x39, {0x39, AND, ABSOLUTE_Y, 3, 4}},
    {0x21, {0x21, AND, INDIRECT_X, 2, 6}},
    {0x31, {0x31, AND, INDIRECT_Y, 2, 5}},

    // ASL
    {0x0A, {0x0A, ASL, ACCUMULATOR, 1, 2}},
    {0x06, {0x06, ASL, ZERO_PAGE, 2, 5}},
    {0x16, {0x16, ASL, ZERO_PAGE_X, 2, 6}},
    {0x0E, {0x0E, ASL, ABSOLUTE, 3, 6}},
    {0x1E, {0x1E, ASL, ABSOLUTE_X, 3, 7}},

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

    // STA
    {0x85, {0x85, STA, ZERO_PAGE, 2, 3}},
    {0x95, {0x95, STA, ZERO_PAGE_X, 2, 4}},
    {0x8D, {0x8D, STA, ABSOLUTE, 3, 4}},
    {0x9D, {0x9D, STA, ABSOLUTE_X, 3, 5}},
    {0x99, {0x99, STA, ABSOLUTE_Y, 3, 5}},
    {0x81, {0x81, STA, INDIRECT_X, 2, 6}},
    {0x91, {0x91, STA, INDIRECT_Y, 2, 6}},

    // STX
    {0x86, {0x86, STX, ZERO_PAGE, 2, 3}},
    {0x96, {0x96, STX, ZERO_PAGE_Y, 2, 4}},
    {0x8E, {0x8E, STX, ABSOLUTE, 3, 4}},

    // STY
    {0x84, {0x84, STY, ZERO_PAGE, 2, 3}},
    {0x94, {0x94, STY, ZERO_PAGE_X, 2, 4}},
    {0x8C, {0x8C, STY, ABSOLUTE, 3, 4}},

    // TAX
    {0xAA, {0xAA, TAX, IMPLIED, 1, 2}},

    // TAY
    {0xA8, {0xA8, TAY, IMPLIED, 1, 2}},

    // TSX
    {0xBA, {0xBA, TSX, IMPLIED, 1, 2}},

    // TXA
    {0x8A, {0x8A, TXA, IMPLIED, 1, 2}},

    // TXS
    {0x9A, {0x9A, TXS, IMPLIED, 1, 2}},

    // TYA
    {0x98, {0x98, TYA, IMPLIED, 1, 2}},
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
        case AND:
            return "AND";
        case ASL:
            return "ASL";
        case BRK:
            return "BRK";
        case INX:
            return "INX";
        case LDA:
            return "LDA";
        case STA:
            return "STA";
        case STX:
            return "STX";
        case STY:
            return "STY";
        case TAX:
            return "TAX";
        case TAY:
            return "TAY";
        case TSX:
            return "TSX";
        case TXA:
            return "TXA";
        case TXS:
            return "TXS";
        case TYA:
            return "TYA";
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
        case ZERO_PAGE_Y:
            return "ZERO_PAGE_Y";
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
