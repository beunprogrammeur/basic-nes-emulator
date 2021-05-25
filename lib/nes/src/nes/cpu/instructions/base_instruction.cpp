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

    uint16_t BaseInstruction::getZeroPageXYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t xy)
    {
        return (bus.read(registers.pc+1) + static_cast<int8_t>(xy)) & 0xff;
    }

    uint16_t BaseInstruction::indirectXAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
    {
        return (bus.read(registers.pc + 1) + static_cast<int8_t>(registers.x)) & 0xff;
    }

    uint16_t BaseInstruction::indirectYAddr(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, bool& pageCrossed)
    {
        uint16_t    addr = bus.read(bus.read(registers.pc + 1));
        auto page = addr & 0xff00;
        
        addr += static_cast<int8_t>(registers.y);
        
        pageCrossed = page != (addr & 0xff00);

        return addr;
    }

    void BaseInstruction::setNZ(nes::cpu::Registers& registers, uint8_t input)
    {
        registers.p.z =  input == 0x00;
        registers.p.n = (input &  0x80) > 0;
    }

    uint8_t BaseInstruction::ldTargetImmediate(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target)
    {
        target = bus.read(registers.pc + 1);
        setNZ(registers, target);
        registers.pc += 2;
        return 2;
    }

    uint8_t BaseInstruction::ldTargetZeroPage(nes::cpu::Registers& registers,  nes::cpu::bus::IBus& bus, uint8_t& target)
    {
        target = bus.read(bus.read(registers.pc + 1));
        setNZ(registers, target);
        registers.pc += 2;
        return 3;
    }

    uint8_t BaseInstruction::ldTargetZeroPageXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target, uint8_t xy)
    {
        target = bus.read(getZeroPageXYAddr(registers, bus, xy));
        setNZ(registers, target);
        registers.pc += 2;
        return 4;
    }

    uint8_t BaseInstruction::ldTargetAbsolute(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target)
    {
        target = bus.read(read16(bus, registers.pc + 1));
        setNZ(registers, target);
        registers.pc += 2;
        return 4;
    }

    uint8_t BaseInstruction::ldTargetAbsoluteXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t& target, uint8_t xy)
    {
        bool pageCrossed;
        uint16_t ptr = getABSXYAddr(registers, bus, xy, pageCrossed);
        target = bus.read(ptr);
        setNZ(registers, target);
        registers.pc += 3;
        return 4 + pageCrossed;
    }

    uint8_t BaseInstruction::storeZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value)
    {
        bus.write(bus.read(registers.pc + 1), value);
        registers.pc += 2;
        return 3;
    }

    uint8_t BaseInstruction::storeABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value)
    {
        bus.write(read16(bus, registers.pc + 1), value);
        registers.pc += 3;
        return 4;
    }

    uint8_t BaseInstruction::storeZPXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value, uint8_t xy)
    {
        bus.write(getZeroPageXYAddr(registers, bus, xy), value);
        registers.pc += 2;
        return 4;
    }

    uint8_t BaseInstruction::storeABSXY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value, uint8_t xy)
    {
        bool pageCrossed;
        bus.write(getABSXYAddr(registers, bus, xy, pageCrossed), value);
        registers.pc += 3;
        return 5;
    }

    // http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    void BaseInstruction::performADC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value)
    {
        uint16_t sum  = registers.a + value + registers.p.c; 
        registers.p.c = sum > 0xff;
        registers.p.v = ~(registers.a ^ value) & (registers.a ^sum) & 0x80;
        setNZ(registers, sum);
        registers.a = static_cast<uint8_t>(sum);
    }
    
    // http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    void BaseInstruction::performSBC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, uint8_t value)
    {
        uint16_t sum = registers.a + ~value + registers.p.c;
        registers.p.c = (sum & 0xff00) > 0;
        registers.p.v = ~(registers.a ^ ~value) & (registers.a ^ sum) & 0x80;
        setNZ(registers, sum);
        registers.a = sum;        
    }

    void BaseInstruction::compare(nes::cpu::Registers& registers, uint8_t& reg, uint8_t memory)
    {
        registers.p.c = reg >= memory;
        setNZ(registers, reg - memory);
    }

    uint8_t BaseInstruction::branch(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus, bool doBranch)
    {
        uint8_t ticks = 2;

        if(doBranch)
        {
            ticks++;

            int8_t offset = static_cast<int8_t>(bus.read(registers.pc + 1));
            uint16_t page = registers.pc  & 0xff00;
            registers.pc += offset;
            ticks += page != (registers.pc & 0xff00);
        }
        else
        {
            registers.pc += 2;
        }

        return ticks;
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