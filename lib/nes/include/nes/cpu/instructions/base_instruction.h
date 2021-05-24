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

    

protected:
    // stack operations
    void    push(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value);
    uint8_t pull(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);

    uint16_t read16(nes::cpu::bus::IBus& bus, uint16_t addr);

    uint16_t getABSXYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t reg, bool& pageCrossed);
    uint16_t getZeroPageXYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t xy);

    uint16_t indirectXAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus);
    uint16_t indirectYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, bool& pageCrossed);

    void    setNZ(nes::cpu::Registers& registers, uint8_t input);

    // LD[x,y,a]
    uint8_t ldTargetImmediate(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target);
    uint8_t ldTargetZeroPage(nes::cpu::Registers& registers,  nes::cpu::bus::IBus& bus, uint8_t& target);
    uint8_t ldTargetZeroPageXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target, uint8_t xy);
    uint8_t ldTargetAbsolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target);
    uint8_t ldTargetAbsoluteXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target, uint8_t xy);

    // ST[x,y,a]
    uint8_t storeZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value);
    uint8_t storeZPXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value, uint8_t xy);
    uint8_t storeABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value);
    uint8_t storeABSXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value, uint8_t xy);

    //adc helper
    void performADC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value);
    void performSBC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value);

    //cmp, cpx, cpy helpers
    void compare(nes::cpu::Registers& registers, uint8_t& reg, uint8_t memory);

public:
    BaseInstruction(std::string&& name, IInstructionErrorHandler& instructionErrorHandler);
    virtual uint8_t execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual const std::string& name() const         { return _name; }
    virtual void setMode(const AddressingMode mode) { _mode = mode; }
    virtual AddressingMode getMode() const          { return _mode; }
};
}