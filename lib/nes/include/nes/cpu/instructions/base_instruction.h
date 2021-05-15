#pragma once
#include <nes/cpu/instructions/iinstruction.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>

namespace nes::cpu::instructions
{
class BaseInstruction : public IInstruction
{
private:
    std::string _name;
    IInstructionErrorHandler& _handler;

    virtual uint8_t ZeroPage(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IndexedZeroPage(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Absolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IndexedAbsolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Indirect(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Implied(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Accumulator(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Immediate(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Relative(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IndexedIndirect(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IndirectIndexed(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t Unknown(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    

public:
    BaseInstruction(std::string&& name, IInstructionErrorHandler& instructionErrorHandler);
    virtual uint8_t execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, AddressingMode mode) override;
    virtual const std::string& name() const { return _name; }
};
}