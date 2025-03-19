#pragma once

#include <string>

#include "byte.h"

enum instruction : b1
{
    AND,
    BRK,
    INX,
    LDA,
    STA,
    STX,
    STY,
    TAX,
};

enum addressMode : uint8_t
{
    IMPLIED,
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y,
};

struct opCode
{
    b1 code;
    instruction instr;
    addressMode addrMode;
    uint8_t numBytes;
    uint8_t numCycles;
};

const opCode& lookupCode(b1 b);

std::string instrStr(const instruction instr);
std::string addrModeStr(const addressMode mode);
void print(const opCode& c);

