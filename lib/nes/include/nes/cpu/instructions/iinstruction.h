#pragma once
#include <nes/cpu/registers.h>
#include <nes/cpu/bus/bus.h>
#include <string>

namespace nes::instructions
{

enum class AddressingMode
{
    ZeroPage,
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
    IInstruction(std::string& name);
    virtual void Execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, AddressingMode mode) = 0;
};

}