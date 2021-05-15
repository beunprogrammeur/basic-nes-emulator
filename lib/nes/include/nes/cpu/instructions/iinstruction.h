#pragma once
#include <nes/cpu/registers.h>
#include <nes/cpu/bus/bus.h>
#include <string>

namespace nes::cpu::instructions
{

enum class AddressingMode
{
    // Unknown: not defined. No addresing mode.
    UNK,
    // Absolute addressing
    ABS,
    // Absolute indexed X addressing
    ABSX,
    // Absolute indexed Y addressing
    ABSY,
    // Accumulator addressing
    ACC,
    // Indirect absolute addressing
    IABS,
    // Indirect absolute indexed X addressing
    IABSX,
    // Indirect Indexed addressing
    IIND,
    // Indirect Indexed X addressing
    IINDX,
    // Indirect Indexed Y addressing
    IINDY,
    // Immediate addressing
    IMM,
    // Implied addressing
    IMP,
    // Relative addressing
    REL,
    // Zero page addressing
    ZP,
    // Zero page indexed X addressing
    ZPX,
    // Zero page indexed Y addressing
    ZPY,
};

class IInstruction
{
    // executes the current instruction.
    // returns the number of ticks this instruction costs
    virtual uint8_t execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) = 0;
    virtual const std::string& name() const = 0;
};

}