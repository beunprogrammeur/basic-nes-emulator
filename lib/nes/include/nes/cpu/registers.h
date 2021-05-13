#pragma once
#include <stdint.h>

namespace nes::cpu
{

struct ProcessorStatusRegister
{
public:
    // Negative (1 = negative)
    bool n : 1;
    // Overflow 1 = true
    bool v : 2;
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
    // 9 bits stack pointer
    uint16_t sp;
    // Processor status register
    ProcessorStatusRegister p;
};

}