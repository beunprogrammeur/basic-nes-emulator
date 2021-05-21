#pragma once
#include <stdint.h>

namespace nes::cpu
{

struct ProcessorStatusRegister
{
public:
    // Negative (1 = negative)
    bool n : 1;
    // Unused bit. do not alter.
    bool u : 1;
    // Overflow 1 = true
    bool v : 1;
    // BRK command
    bool b : 1;
    // Decimal Mode 1 = true (not used for the NES)
    bool d : 1;
    // IRQ disable 1 = disabled
    bool i : 1;
    // Zero 1 = result zero
    bool z : 1;
    // Carry 1 = true
    bool c : 1;
};

struct Registers
{
    // Accumulator
    uint8_t a;
    // Index register y
    uint8_t x;
    // Index register y
    uint8_t y;
    // 16 bits program counter (pch, pcl)
    uint16_t pc;
    // 8 bits stack pointer, wraps around. no stack overflow detection.
    uint8_t sp;
    // Processor status register
    ProcessorStatusRegister p;

    void reset() { reset(0xfffc); } // default boot address
    void reset(uint16_t startAddress)  { a = 0; x = 0; y = 0; pc = 0; sp = 0xfd; p.n = 0; p.u = true; p.v = false; p.b = false; p.d = false; p.i = false; p.z = false; p.c = false;}
    bool operator==(const Registers& r) const
    {
        return a   == r.a   &&
               x   == r.x   &&
               y   == r.y   &&
               pc  == r.pc  &&
               p.n == r.p.n &&
               p.u == r.p.u &&
               p.v == r.p.v &&
               p.b == r.p.b &&
               p.d == r.p.d &&
               p.i == r.p.i &&
               p.z == r.p.z &&
               p.c == r.p.c;
    }
};

}