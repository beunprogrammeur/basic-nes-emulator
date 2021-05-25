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

    uint8_t toByte() const { return n << 7 | u << 6 | v << 5 | b << 4 | d << 3 | i << 2 | z << 1 | c; }
    void    fromByte(uint8_t data) { 
        n = data & (1 << 7); 
        u = data & (1 << 6);
        v = data & (1 << 5);
        b = data & (1 << 4);
        d = data & (1 << 3);
        i = data & (1 << 2);
        z = data & (1 << 1);
        c = data & (1 << 0);
    }
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
};

}