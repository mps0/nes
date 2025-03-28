// cpu.cpp

#include "cpu.h"
#include <cstdio>
#include <iostream>

CPU::CPU(Memory& mem) :
    m_mem(mem)
{
    reset();
}

void CPU::reset()
{
    m_sp = 0;
    m_status = 0;
    m_regA = 0;
    m_regX = 0;
    m_pc = Memory::PROG_START;
    m_run = true;
}
void CPU::run()
{
    while(m_run)
    {
        evaluate();
    }
}

void CPU::run(uint32_t numInstr)
{
    for(uint32_t i = 0; i < numInstr; ++i)
    {
        evaluate();
    }
}

void CPU::evaluate()
{
    const opCode& code = lookupCode(eat());
    print(code);

    switch(code.instr)
    {
        case AND:
            return _and(code);
        case ASL:
            return asl(code);
        case BCC:
            return bcc(code);
        case BCS:
            return bcs(code);
        case BEQ:
            return beq(code);
        case BIT:
            return bit(code);
        case BMI:
            return bmi(code);
        case BNE:
            return bne(code);
        case BRK:
            return brk(code);
        case BPL:
            return bpl(code);
        case BVC:
            return bvc(code);
        case BVS:
            return bvs(code);
        case CLC:
            return clc(code);
        case CLD:
            return cld(code);
        case CLI:
            return cli(code);
        case CLV:
            return clv(code);
        case CMP:
            return cmp(code);
        case CPX:
            return cpx(code);
        case CPY:
            return cpy(code);
        case DEC:
            return dec(code);
        case DEX:
            return dex(code);
        case DEY:
            return dey(code);
        case EOR:
            return eor(code);
        case INC:
            return inc(code);
        case INX:
            return inx(code);
        case INY:
            return iny(code);
        case JMP:
            return jmp(code);
        case JSR:
            return jsr(code);
        case LDA:
            return lda(code);
        case LDX:
            return ldx(code);
        case LDY:
            return ldy(code);
        case LSR:
            return lsr(code);
        case NOP:
            return nop(code);
        case ORA:
            return ora(code);
        case PHA:
            return pha(code);
        case PHP:
            return php(code);
        case PLA:
            return pla(code);
        case PLP:
            return plp(code);
        case ROL:
            return rol(code);
        case ROR:
            return ror(code);
        case RTI:
            return rti(code);
        case RTS:
            return rts(code);
        case SBC:
            return sbc(code);
        case STA:
            return sta(code);
        case STX:
            return stx(code);
        case STY:
            return sty(code);
        case TAX:
            return tax(code);
        case TAY:
            return tay(code);
        case TSX:
            return tsx(code);
        case TXA:
            return txa(code);
        case TXS:
            return txs(code);
        case TYA:
            return tya(code);
        default:
            printf("Couldn't find case for code!");
            return brk(code);
    };
}

b2 CPU::getAddr(addressMode mode)
{
    b2 fb = static_cast<b2>(eat());
    switch(mode)
    {
        case IMMEDIATE:
            return m_pc - 1;
        case ZERO_PAGE:
            return fb;
        case ZERO_PAGE_X:
            return fb + m_regX;
        case ZERO_PAGE_Y:
            return fb + m_regY;
        case ABSOLUTE:
            return (fb << 8) | eat();
        case ABSOLUTE_X:
            return (fb << 8) | (eat() + m_regX);
        case ABSOLUTE_Y:
            return (fb << 8) | (eat() + m_regY);
        case INDIRECT:
            {
                b2 addr = (fb << 8) | eat();
                b2 lo = m_mem.read1(addr);
                b2 hi = m_mem.read1(addr + 1);
                return (hi << 8) | lo;
            }
        case INDIRECT_X:
            {
                b1 zpAddr = fb + m_regX;
                b2 lo = m_mem.read1(zpAddr);
                b2 hi = m_mem.read1(b1(zpAddr + 1));
                return (hi << 8) | lo;
            }
        case INDIRECT_Y:
            {
                b1 zpAddr = fb;
                b2 lo = m_mem.read1(zpAddr);
                b2 hi = m_mem.read1(b1(zpAddr + 1));
                return ((hi << 8) | lo) + m_regY;
            }

        case RELATIVE:
                return fb;

        case ACCUMULATOR:
        default:
            return 0x0;
    }
}

b1 CPU::eat()
{
    b1 k = m_mem.read1(m_pc++);
    return k;
}

b1 CPU::get()
{
    return m_mem.read1(m_pc);
}

void CPU::setStatusBit(statusBit bit, bool set)
{
    if(set)
        m_status |= bit;
    else
        m_status &= ~bit;
}

bool CPU::isStatusBitSet(statusBit bit)
{
    return m_status & bit;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void CPU::branch(const opCode& code)
{
    b1 loc = getAddr(code.addrMode);
    m_pc = negBitSet(loc) ? m_pc - (0x0100 - loc) : m_pc + loc;
}

void CPU::_and(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 mask = m_mem.read1(loc);

    m_regA &= mask;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::asl(const opCode& code)
{
    if(code.addrMode == ACCUMULATOR)
    {
        setStatusBit(CARRY_FLAG, m_regA & 0x80);
        m_regA = m_regA << 1;

        setStatusBit(ZERO_FLAG, m_regA == 0);
        setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
    }
    else
    {
        b2 loc = getAddr(code.addrMode);
        b1 val = m_mem.read1(loc);

        setStatusBit(CARRY_FLAG, val & 0x80);

        val = val << 1;
        m_mem.write1(loc, val);

        setStatusBit(ZERO_FLAG, val == 0);
        setStatusBit(NEGATIVE_FLAG, negBitSet(val));
    }
}

void CPU::lda(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_regA = m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::ldx(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_regX = m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::ldy(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_regY = m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, m_regY == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regY));
}

void CPU::lsr(const opCode& code)
{
    if(code.addrMode == ACCUMULATOR)
    {
        setStatusBit(CARRY_FLAG, m_regA & 0x01);
        m_regA = m_regA >> 1;

        setStatusBit(ZERO_FLAG, m_regA == 0);
        setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
    }
    else
    {
        b2 loc = getAddr(code.addrMode);
        b1 val = m_mem.read1(loc);

        setStatusBit(CARRY_FLAG, val & 0x01);

        val = val >> 1;
        m_mem.write1(loc, val);

        setStatusBit(ZERO_FLAG, val == 0);
        setStatusBit(NEGATIVE_FLAG, negBitSet(val));
    }
}

void CPU::nop(const opCode& code)
{
}

void CPU::ora(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 mask = m_mem.read1(loc);

    m_regA |= mask;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::pha(const opCode& code)
{
    m_mem.write1(Memory::STACK_START + m_sp, m_regA);
    ++m_sp;
}

void CPU::php(const opCode& code)
{
    m_mem.write1(Memory::STACK_START + m_sp, m_status);
    ++m_sp;
}

void CPU::pla(const opCode& code)
{
    m_regA = m_mem.read1(Memory::STACK_START + m_sp - 1);
    --m_sp;

    setStatusBit(ZERO_FLAG, m_regA == 0);
}

void CPU::plp(const opCode& code)
{
    m_status = m_mem.read1(Memory::STACK_START + m_sp - 1);
    --m_sp;
}

void CPU::rol(const opCode& code)
{
    if(code.addrMode == ACCUMULATOR)
    {
        b1 newVal = m_regA << 1;
        b1 mask = isStatusBitSet(CARRY_FLAG) ? 0x01 : 0x00;
        newVal |= mask;

        setStatusBit(CARRY_FLAG, m_regA & 0x80);

        m_regA = newVal;
    }
    else
    {
        b2 loc = getAddr(code.addrMode);
        b1 val = m_mem.read1(loc);
        b1 newVal = val << 1;
        b1 mask = isStatusBitSet(CARRY_FLAG) ? 0x01 : 0x00;
        newVal |= mask;

        setStatusBit(CARRY_FLAG, newVal & 0x80);

        m_mem.write1(loc, newVal);
    }
}

void CPU::ror(const opCode& code)
{
    if(code.addrMode == ACCUMULATOR)
    {
        b1 newVal = m_regA >> 1;
        b1 mask = isStatusBitSet(CARRY_FLAG) ? 0x80 : 0x00;
        newVal |= mask;

        setStatusBit(CARRY_FLAG, m_regA & 0x01);

        m_regA = newVal;
    }
    else
    {
        b2 loc = getAddr(code.addrMode);
        b1 val = m_mem.read1(loc);
        b1 newVal = val >> 1;
        b1 mask = isStatusBitSet(CARRY_FLAG) ? 0x80 : 0x00;
        newVal |= mask;

        setStatusBit(CARRY_FLAG, newVal & 0x01);

        m_mem.write1(loc, newVal);
    }
}

void CPU::rti(const opCode& code)
{
}

void CPU::rts(const opCode& code)
{
}

void CPU::sbc(const opCode& code)
{
}

void CPU::bcc(const opCode& code)
{
    if(!(isStatusBitSet(CARRY_FLAG)))
        branch(code);
}

void CPU::bcs(const opCode& code)
{
    if(isStatusBitSet(CARRY_FLAG))
        branch(code);
}

void CPU::beq(const opCode& code)
{
    if(isStatusBitSet(ZERO_FLAG))
        branch(code);
}

void CPU::bit(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 res = m_regA & m_mem.read1(loc);

    setStatusBit(ZERO_FLAG, res == 0);
    setStatusBit(OVERFLOW_FLAG, overflowBitSet(res));
    setStatusBit(NEGATIVE_FLAG, negBitSet(res));
}

void CPU::bmi(const opCode& code)
{
    if(isStatusBitSet(NEGATIVE_FLAG))
        branch(code);
}

void CPU::bne(const opCode& code)
{
    if(!(isStatusBitSet(ZERO_FLAG)))
        branch(code);
}

void CPU::bpl(const opCode& code)
{
    if(!(isStatusBitSet(NEGATIVE_FLAG)))
        branch(code);
}

void CPU::brk(const opCode& code)
{
    m_pc = m_mem.read2(Memory::BRK_ADDR);

    //printf("m_pc: %X, BRK_ADDR: %X\n", m_pc, Memory::BRK_ADDR);
    setStatusBit(BREAK_COMMND, true);
    m_run = false;
}

void CPU::bvc(const opCode& code)
{
    if(!(isStatusBitSet(OVERFLOW_FLAG)))
        branch(code);
}

void CPU::bvs(const opCode& code)
{
    if(isStatusBitSet(OVERFLOW_FLAG))
        branch(code);
}

void CPU::clc(const opCode& code)
{
    setStatusBit(CARRY_FLAG, false);
}

void CPU::cld(const opCode& code)
{
    setStatusBit(DECIMAL_MODE_FLAG, false);
}

void CPU::cli(const opCode& code)
{
    setStatusBit(INTERUPT_DISABLE_FLAG, false);
}

void CPU::clv(const opCode& code)
{
    setStatusBit(OVERFLOW_FLAG, false);
}

void CPU::cmp(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    setStatusBit(CARRY_FLAG, m_regA >= val);
    setStatusBit(ZERO_FLAG, m_regA == val);
    setStatusBit(NEGATIVE_FLAG, m_regA < val);
}

void CPU::cpx(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    setStatusBit(CARRY_FLAG, m_regX >= val);
    setStatusBit(ZERO_FLAG, m_regX == val);
    setStatusBit(NEGATIVE_FLAG, m_regX < val);
}

void CPU::cpy(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    setStatusBit(CARRY_FLAG, m_regY >= val);
    setStatusBit(ZERO_FLAG, m_regY == val);
    setStatusBit(NEGATIVE_FLAG, m_regY < val);
}

void CPU::dec(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    --val;

    m_mem.write1(loc, val);

    setStatusBit(ZERO_FLAG, val == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(val));
}

void CPU::dex(const opCode& code)
{
    --m_regX;

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::dey(const opCode& code)
{
    --m_regY;

    setStatusBit(ZERO_FLAG, m_regY == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regY));
}

void CPU::eor(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    m_regA ^= val;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::inc(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    b1 val = m_mem.read1(loc);

    ++val;

    m_mem.write1(loc, val);

    setStatusBit(ZERO_FLAG, val == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(val));
}

void CPU::inx(const opCode& code)
{
    ++m_regX;

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::iny(const opCode& code)
{
    ++m_regY;

    setStatusBit(ZERO_FLAG, m_regY == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regY));
}

void CPU::jmp(const opCode& code)
{
    m_pc = getAddr(code.addrMode);
}

//TODO
void CPU::jsr(const opCode& code)
{
    m_pc = getAddr(code.addrMode);
}

void CPU::sta(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regA);
}

void CPU::stx(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regX);
}

void CPU::sty(const opCode& code)
{
    b2 loc = getAddr(code.addrMode);
    m_mem.write1(loc, m_regY);
}

void CPU::tax(const opCode& code)
{
    m_regX = m_regA;

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::tay(const opCode& code)
{
    m_regY = m_regA;

    setStatusBit(ZERO_FLAG, m_regY == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regY));
}

void CPU::tsx(const opCode& code)
{
    m_regX = m_sp;

    setStatusBit(ZERO_FLAG, m_regX == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regX));
}

void CPU::txa(const opCode& code)
{
    m_regA = m_regX;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

void CPU::txs(const opCode& code)
{
    m_sp = m_regX;

    setStatusBit(ZERO_FLAG, m_sp == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_sp));
}

void CPU::tya(const opCode& code)
{
    m_regA = m_regY;

    setStatusBit(ZERO_FLAG, m_regA == 0);
    setStatusBit(NEGATIVE_FLAG, negBitSet(m_regA));
}

#pragma GCC diagnostic pop

b1 CPU::getA()
{
    return m_regA;
}

b1 CPU::getX()
{
    return m_regX;
}

b1 CPU::getY()
{
    return m_regY;
}

b1 CPU::getSP()
{
    return m_sp;
}

b1 CPU::getStatus()
{
    return m_status;
}

b2 CPU::getPC()
{
    return m_pc;
}

void CPU::setA(b1 v)
{
    m_regA = v;
}

void CPU::setX(b1 v)
{
    m_regX = v;
}

void CPU::setY(b1 v)
{
    m_regY = v;
}

void CPU::setSP(b1 v)
{
    m_sp = v;
}

void CPU::setStatus(b1 v)
{
    m_status = v;
}

void CPU::setPC(b2 v)
{
    m_pc = v;
}
