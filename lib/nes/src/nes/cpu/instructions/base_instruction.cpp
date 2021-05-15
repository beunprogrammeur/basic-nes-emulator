#include <nes/cpu/instructions/base_instruction.h>

namespace nes::cpu::instructions
{
    BaseInstruction::BaseInstruction(std::string&& name, IInstructionErrorHandler& instructionErrorHandler)
        :  _name(name), _handler(instructionErrorHandler)
    {
    }

    uint8_t BaseInstruction::execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, AddressingMode mode)
    {
        uint8_t ticks = 0;
        switch(mode)
        {
            case AddressingMode::ZeroPage:        ticks = ZeroPage(registers, bus);        break;
            case AddressingMode::IndexedZeroPage: ticks = IndexedZeroPage(registers, bus); break;
            case AddressingMode::Absolute:        ticks = Absolute(registers, bus);        break;
            case AddressingMode::IndexedAbsolute: ticks = IndexedAbsolute(registers, bus); break;
            case AddressingMode::Indirect:        ticks = Indirect(registers, bus);        break;
            case AddressingMode::Implied:         ticks = Implied(registers, bus);         break;
            case AddressingMode::Accumulator:     ticks = Accumulator(registers, bus);     break;
            case AddressingMode::Immediate:       ticks = Immediate(registers, bus);       break;
            case AddressingMode::Relative:        ticks = Relative(registers, bus);        break;
            case AddressingMode::IndexedIndirect: ticks = IndexedIndirect(registers, bus); break;
            case AddressingMode::IndirectIndexed: ticks = IndirectIndexed(registers, bus); break;
            case AddressingMode::Unknown:         ticks = Unknown(registers, bus);         break;
        }

        return ticks;
    }

    // TODO: call the error handler for unsupported instruction mode use.
    uint8_t BaseInstruction::ZeroPage(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)        { _handler.invalidMode(*this, AddressingMode::ZeroPage);        return 0; }
    uint8_t BaseInstruction::IndexedZeroPage(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IndexedZeroPage); return 0; }
    uint8_t BaseInstruction::Absolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)        { _handler.invalidMode(*this, AddressingMode::Absolute);        return 0; }
    uint8_t BaseInstruction::IndexedAbsolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IndexedAbsolute); return 0; }
    uint8_t BaseInstruction::Indirect(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)        { _handler.invalidMode(*this, AddressingMode::Indirect);        return 0; }
    uint8_t BaseInstruction::Implied(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)         { _handler.invalidMode(*this, AddressingMode::Implied);         return 0; }
    uint8_t BaseInstruction::Accumulator(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)     { _handler.invalidMode(*this, AddressingMode::Accumulator);     return 0; }
    uint8_t BaseInstruction::Immediate(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)       { _handler.invalidMode(*this, AddressingMode::Immediate);       return 0; }
    uint8_t BaseInstruction::Relative(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)        { _handler.invalidMode(*this, AddressingMode::Relative);        return 0; }
    uint8_t BaseInstruction::IndexedIndirect(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IndexedIndirect); return 0; }
    uint8_t BaseInstruction::IndirectIndexed(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IndirectIndexed); return 0; }
    uint8_t BaseInstruction::Unknown(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)         { _handler.invalidMode(*this, AddressingMode::Unknown);         return 0; }

}