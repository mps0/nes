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

    // BCC
    {0x90, {0x90, BCC, RELATIVE, 2, 2}},

    // BCS
    {0xB0, {0xB0, BCS, RELATIVE, 2, 2}},

    // BEQ
    {0xF0, {0xF0, BEQ, RELATIVE, 2, 2}},

    // BIT
    {0x24, {0x24, BIT, ZERO_PAGE, 2, 3}},
    {0x2C, {0x2C, BIT, ABSOLUTE, 3, 4}},

    // BMI
    {0x30, {0x30, BMI, RELATIVE, 2, 2}},

    // BNE
    {0xD0, {0xd0, BNE, RELATIVE, 2, 2}},

    // BPL
    {0x10, {0x10, BPL, RELATIVE, 2, 2}},

    // BRK
    {0x00, {0x00, BRK, IMPLIED, 1, 7}},

    // BVC
    {0x50, {0x50, BVC, RELATIVE, 2, 2}},

    // BVS
    {0x70, {0x70, BVS, RELATIVE, 2, 2}},

    // CLC
    {0x18, {0x18, CLC, IMPLIED, 1, 2}},

    // CLD
    {0xD8, {0xD8, CLD, IMPLIED, 1, 2}},

    // CLI
    {0x58, {0x58, CLI, IMPLIED, 1, 2}},

    // CLV
    {0xB8, {0xB8, CLV, IMPLIED, 1, 2}},

    // CMP
    {0xC9, {0xC9, CMP, IMMEDIATE, 2, 2}},
    {0xC5, {0xC5, CMP, ZERO_PAGE, 2, 3}},
    {0xD5, {0xD5, CMP, ZERO_PAGE_X, 2, 4}},
    {0xCD, {0xCD, CMP, ABSOLUTE, 3, 4}},
    {0xDD, {0xDD, CMP, ABSOLUTE_X, 3, 4}},
    {0xD9, {0xD9, CMP, ABSOLUTE_Y, 3, 4}},
    {0xC1, {0xC1, CMP, INDIRECT_X, 2, 6}},
    {0xD1, {0xD1, CMP, INDIRECT_Y, 2, 5}},

    // CPX
    {0xE0, {0xE0, CPX, IMMEDIATE, 2, 2}},
    {0xE4, {0xE4, CPX, ZERO_PAGE, 2, 3}},
    {0xEC, {0xEC, CPX, ABSOLUTE, 3, 4}},

    // CPY
    {0xC0, {0xC0, CPY, IMMEDIATE, 2, 2}},
    {0xC4, {0xC4, CPY, ZERO_PAGE, 2, 3}},
    {0xCC, {0xCC, CPY, ABSOLUTE, 3, 4}},

    // DEC
    {0xC6, {0xC6, DEC, ZERO_PAGE, 2, 5}},
    {0xD6, {0xD6, DEC, ZERO_PAGE_X, 2, 6}},
    {0xCE, {0xCE, DEC, ABSOLUTE, 3, 6}},
    {0xDE, {0xDE, DEC, ABSOLUTE_X, 3, 7}},

    // DEX
    {0xCA, {0xCA, DEX, IMPLIED, 1, 2}},

    // DEY
    {0x88, {0x88, DEY, IMPLIED, 1, 2}},

    // EOR
    {0x49, {0x49, EOR, IMMEDIATE, 2, 2}},
    {0x45, {0x45, EOR, ZERO_PAGE, 2, 3}},
    {0x55, {0x55, EOR, ZERO_PAGE_X, 2, 4}},
    {0x4D, {0x4D, EOR, ABSOLUTE, 3, 4}},
    {0x5D, {0x5D, EOR, ABSOLUTE_X, 3, 4}},
    {0x59, {0x59, EOR, ABSOLUTE_Y, 3, 4}},
    {0x41, {0x41, EOR, INDIRECT_X, 2, 6}},
    {0x51, {0x51, EOR, INDIRECT_Y, 2, 5}},

    // INC
    {0xE6, {0xE6, INC, ZERO_PAGE, 2, 5}},
    {0xF6, {0xF6, INC, ZERO_PAGE_X, 2, 6}},
    {0xEE, {0xEE, INC, ABSOLUTE, 3, 6}},
    {0xFE, {0xFE, INC, ABSOLUTE_X, 3, 7}},

    // INX
    {0xE8, {0xE8, INX, IMPLIED, 1, 2}},

    // INY
    {0xC8, {0xC8, INY, IMPLIED, 1, 2}},

    // JMP
    {0x4C, {0x4C, JMP, ABSOLUTE, 3, 3}},
    {0x6C, {0x6C, JMP, INDIRECT, 3, 5}},

    // JSR
    {0x20, {0x20, JSR, ABSOLUTE, 3, 6}},

    // LDA
    {0xA9, {0xA9, LDA, IMMEDIATE, 2, 2}},
    {0xA5, {0xA5, LDA, ZERO_PAGE, 2, 3}},
    {0xB5, {0xB5, LDA, ZERO_PAGE_X, 2, 4}},
    {0xAD, {0xAD, LDA, ABSOLUTE, 3, 4}},
    {0xBD, {0xBD, LDA, ABSOLUTE_X, 3, 4}},
    {0xB9, {0xB9, LDA, ABSOLUTE_Y, 3, 4}},
    {0xA1, {0xA1, LDA, INDIRECT_X, 2, 6}},
    {0xB1, {0xB1, LDA, INDIRECT_Y, 2, 5}},

    // LDX
    {0xA2, {0xA2, LDX, IMMEDIATE, 2, 2}},
    {0xA6, {0xA6, LDX, ZERO_PAGE, 2, 3}},
    {0xB6, {0xB6, LDX, ZERO_PAGE_Y, 2, 4}},
    {0xAE, {0xAE, LDX, ABSOLUTE, 3, 4}},
    {0xBE, {0xBE, LDX, ABSOLUTE_Y, 3, 4}},

    // LDY
    {0xA0, {0xA0, LDY, IMMEDIATE, 2, 2}},
    {0xA4, {0xA4, LDY, ZERO_PAGE, 2, 3}},
    {0xB4, {0xB4, LDY, ZERO_PAGE_X, 2, 4}},
    {0xAC, {0xAC, LDY, ABSOLUTE, 3, 4}},
    {0xBC, {0xBC, LDY, ABSOLUTE_X, 3, 4}},

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
        case BCC:
            return "BCC";
        case BCS:
            return "BCS";
        case BEQ:
            return "BEQ";
        case BIT:
            return "BIT";
        case BMI:
            return "BMI";
        case BNE:
            return "BNE";
        case BRK:
            return "BRK";
        case BPL:
            return "BPL";
        case BVC:
            return "BVC";
        case BVS:
            return "BVS";
        case CLC:
            return "CLC";
        case CLD:
            return "CLD";
        case CLI:
            return "CLI";
        case CLV:
            return "CLV";
        case CMP:
            return "CMP";
        case CPX:
            return "CPX";
        case CPY:
            return "CPY";
        case DEC:
            return "DEC";
        case DEX:
            return "DEX";
        case DEY:
            return "DEY";
        case EOR:
            return "EOR";
        case INC:
            return "INC";
        case INX:
            return "INX";
        case INY:
            return "INY";
        case JMP:
            return "JMP";
        case JSR:
            return "JSR";
        case LDA:
            return "LDA";
        case LDX:
            return "LDX";
        case LDY:
            return "LDY";
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
        case ACCUMULATOR:
            return "ACCUMULATOR";
        case IMPLIED:
            return "IMPLIED";
        case RELATIVE:
            return "RELATIVE";
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
