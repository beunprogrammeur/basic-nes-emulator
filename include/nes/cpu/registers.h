#pragma once
#include <stdint.h>

namespace nes::cpu
{
    struct ProcessorStatus
    {
        // negative flag (sign bit).
        // 1 = signed, 0 = unsigned
        bool n : 1;
        // overflow flag
        // set if 2's complement instruction result is invalid. 
        // a positive number was expected but turned out to be negative.
        bool v : 1;
        // unused bit, this is not a flag.
        bool u : 1;
        // break command
        // is set to true by the BRK instruction, resulting in an IRQ
        bool b : 1;
        // decimal mode (not supported by NES 2A03 cpu, so BCD mode will never be used)
        // set by SED instruction, cleared by CLD instruction.
        bool d : 1;
        // interrupt disable
        bool i : 1;
        // zero flag
        bool z : 1;
        // carry flag
        bool c : 1;
    };

    struct Registers
    {
        // status register
        ProcessorStatus p;
        // accumulator
        uint8_t a;
        // index register x
        uint8_t x;
        // index register y
        uint8_t y;
        // stack pointer
        uint8_t sp;
        // program counter
        uint8_t pc;
    };
}