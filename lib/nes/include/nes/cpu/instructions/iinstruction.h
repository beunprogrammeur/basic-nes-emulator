#pragma once
#include <nes/cpu/registers.h>
#include <nes/cpu/bus/bus.h>
#include <string>

namespace nes::cpu::instructions
{

enum class AddressingMode
{
    // Used for pointing to addresses between 0x0000 and 0x00FF.
    // Because the address is so low, only one byte as opperand is needed
    // Thus saving ticks.
    ZeroPage,
    // Same as ZeroPage, makes use of the Index x/y registers to add a value 
    IndexedZeroPage,
    Absolute,
    IndexedAbsolute,
    Indirect,
    Implied,
    Accumulator,
    Immediate,
    Relative,
    IndexedIndirect,
    IndirectIndexed,
};

class IInstruction
{
    // executes the current instruction.
    // returns the number of ticks this instruction costs
    virtual uint8_t execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, AddressingMode mode) = 0;
    virtual const std::string& name() const = 0;
};

}