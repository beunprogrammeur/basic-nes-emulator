#pragma once
#include <nes/cpu/instructions/iinstruction.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>

namespace nes::cpu::instructions
{
class BaseInstruction : public IInstruction
{
private:
    std::string _name;
    AddressingMode _mode;
    IInstructionErrorHandler& _handler;

    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IIND(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t UNK(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    virtual uint8_t ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);

    

public:
    BaseInstruction(std::string&& name, IInstructionErrorHandler& instructionErrorHandler);
    virtual uint8_t execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual const std::string& name() const         { return _name; }
    virtual void setMode(const AddressingMode mode) { _mode = mode; }
    virtual AddressingMode getMode() const          { return _mode; }
};
}