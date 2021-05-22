#include <nes/cpu/instructions/base_instruction.h>

namespace nes::cpu::instructions
{
    BaseInstruction::BaseInstruction(std::string&& name, IInstructionErrorHandler& instructionErrorHandler)
        :  _name(name), _mode(AddressingMode::UNK), _handler(instructionErrorHandler)
    {
    }

    uint8_t BaseInstruction::execute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
    {
        uint8_t ticks = 0;
        switch(_mode)
        {
            case AddressingMode::ABS:   ticks = ABS(registers,   bus); break;
            case AddressingMode::ABSX:  ticks = ABSX(registers,  bus); break;
            case AddressingMode::ABSY:  ticks = ABSY(registers,  bus); break;
            case AddressingMode::ACC:   ticks = ACC(registers,   bus); break;
            case AddressingMode::IABS:  ticks = IABS(registers,  bus); break;
            case AddressingMode::IABSX: ticks = IABSX(registers, bus); break;
            case AddressingMode::IIND:  ticks = IIND(registers,  bus); break;
            case AddressingMode::IINDX: ticks = IINDX(registers, bus); break;
            case AddressingMode::IINDY: ticks = IINDY(registers, bus); break;
            case AddressingMode::IMM:   ticks = IMM(registers,   bus); break;
            case AddressingMode::IMP:   ticks = IMP(registers,   bus); break;
            case AddressingMode::REL:   ticks = REL(registers,   bus); break;
            case AddressingMode::UNK:   ticks = UNK(registers,   bus); break;
            case AddressingMode::ZP:    ticks = ZP(registers,    bus); break;
            case AddressingMode::ZPX:   ticks = ZPX(registers,   bus); break;
            case AddressingMode::ZPY:   ticks = ZPY(registers,   bus); break;
        }

        return ticks;
    }

    void    BaseInstruction::push(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value)
    {
        bus.write(0x0100 | registers.sp, value);
        registers.sp--; // The stack starts at the end of a page, and grows towards the beginning of the page.
    }

    uint8_t BaseInstruction::pull(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
    {
        registers.sp++; // stack pointer points towards the next 'available' space.
        return bus.read(0x0100 | registers.sp);
    }

    uint16_t BaseInstruction::read16(nes::cpu::bus::IBus& bus, uint16_t addr)
    {
        return bus.read(addr)     |
               bus.read(addr + 1) << 8;
    }

    uint16_t BaseInstruction::getABSXYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t reg, bool& pageCrossed)
    {
        auto addr = read16(bus, registers.pc + 1);
        auto page = addr & 0xff00;
        addr += static_cast<int8_t>(reg);
        pageCrossed = (page != (addr & 0xff00));
        return addr;
    }

    uint16_t BaseInstruction::getZeroPageXAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
    {
        return (bus.read(registers.pc+1) + registers.x) & 0xff;
    }

    uint8_t BaseInstruction::indirectX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
    {
        return bus.read(bus.read(registers.pc + 1) + registers.x);
    }

    uint8_t BaseInstruction::indirectY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, bool& pageCrossed)
    {
        uint16_t    addr = bus.read(bus.read(registers.pc + 1));
        auto page = addr & 0xff00;
        
        addr += static_cast<int8_t>(registers.y);
        
        pageCrossed = page != (addr & 0xff00);

        return bus.read(addr);
    }

    void BaseInstruction::setNZ(nes::cpu::Registers& registers, uint8_t input)
    {
        registers.p.z =  input == 0x00;
        registers.p.n = (input &  0x80) > 0;
    }

    uint8_t BaseInstruction::ABS(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ABS);   return 0; }
    uint8_t BaseInstruction::ABSX(nes::cpu::Registers&  registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ABSX);  return 0; }
    uint8_t BaseInstruction::ABSY(nes::cpu::Registers&  registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ABSY);  return 0; }
    uint8_t BaseInstruction::ACC(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ACC);   return 0; }
    uint8_t BaseInstruction::IABS(nes::cpu::Registers&  registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IABS);  return 0; }
    uint8_t BaseInstruction::IABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IABSX); return 0; }
    uint8_t BaseInstruction::IIND(nes::cpu::Registers&  registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IIND);  return 0; }
    uint8_t BaseInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IINDX); return 0; }
    uint8_t BaseInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IINDY); return 0; }
    uint8_t BaseInstruction::IMM(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IMM);   return 0; }
    uint8_t BaseInstruction::IMP(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::IMP);   return 0; }
    uint8_t BaseInstruction::REL(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::REL);   return 0; }
    uint8_t BaseInstruction::UNK(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::UNK);   return 0; }
    uint8_t BaseInstruction::ZP(nes::cpu::Registers&    registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ZP);    return 0; }
    uint8_t BaseInstruction::ZPX(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ZPX);   return 0; }
    uint8_t BaseInstruction::ZPY(nes::cpu::Registers&   registers, nes::cpu::bus::IBus& bus) { _handler.invalidMode(*this, AddressingMode::ZPY);   return 0; }
}