#include <nes/cpu/instructions/instructions.h>

namespace nes::cpu::instructions
{
// constructors
ADCInstruction::ADCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ADC", handler) {}
ANDInstruction::ANDInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("AND", handler) {}
ASLInstruction::ASLInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ASL", handler) {}
BCCInstruction::BCCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BCC", handler) {}
BCSInstruction::BCSInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BCS", handler) {}
BEQInstruction::BEQInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BEQ", handler) {}
BITInstruction::BITInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BIT", handler) {}
BMIInstruction::BMIInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BMI", handler) {}
BNEInstruction::BNEInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BNE", handler) {}
BPLInstruction::BPLInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BPL", handler) {}
BRKInstruction::BRKInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BRK", handler) {}
BVCInstruction::BVCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BVC", handler) {}
BVSInstruction::BVSInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("BVS", handler) {}
CLCInstruction::CLCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CLC", handler) {}
CLDInstruction::CLDInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CLD", handler) {}
CLIInstruction::CLIInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CLI", handler) {}
CLVInstruction::CLVInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CLV", handler) {}
CMPInstruction::CMPInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CMP", handler) {}
CPXInstruction::CPXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CPX", handler) {}
CPYInstruction::CPYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("CPY", handler) {}
DECInstruction::DECInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("DEC", handler) {}
DEXInstruction::DEXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("DEX", handler) {}
DEYInstruction::DEYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("DEY", handler) {}
EORInstruction::EORInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("EOR", handler) {}
INCInstruction::INCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("INC", handler) {}
INXInstruction::INXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("INX", handler) {}
INYInstruction::INYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("INY", handler) {}
JMPInstruction::JMPInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("JMP", handler) {}
JSRInstruction::JSRInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("JSR", handler) {}
LDAInstruction::LDAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("LDA", handler) {}
LDXInstruction::LDXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("LDX", handler) {}
LDYInstruction::LDYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("LDY", handler) {}
LSRInstruction::LSRInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("LSR", handler) {}
NOPInstruction::NOPInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("NOP", handler) {}
ORAInstruction::ORAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ORA", handler) {}
PHAInstruction::PHAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("PHA", handler) {}
PHPInstruction::PHPInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("PHP", handler) {}
PLAInstruction::PLAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("PLA", handler) {}
PLPInstruction::PLPInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("PLP", handler) {}
ROLInstruction::ROLInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ROL", handler) {}
RORInstruction::RORInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ROR", handler) {}
RTIInstruction::RTIInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("RTI", handler) {}
RTSInstruction::RTSInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("RTS", handler) {}
SBCInstruction::SBCInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("SBC", handler) {}
SECInstruction::SECInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("SEC", handler) {}
SEDInstruction::SEDInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("SED", handler) {}
SEIInstruction::SEIInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("SEI", handler) {}
STAInstruction::STAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("STA", handler) {}
STXInstruction::STXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("STX", handler) {}
STYInstruction::STYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("STY", handler) {}
TAXInstruction::TAXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TAX", handler) {}
TAYInstruction::TAYInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TAY", handler) {}
TSXInstruction::TSXInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TSX", handler) {}
TXAInstruction::TXAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TXA", handler) {}
TXSInstruction::TXSInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TXS", handler) {}
TYAInstruction::TYAInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("TYA", handler) {}


//
// BRK
//

uint8_t BRKInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    constexpr uint16_t IRQInterruptVector = 0xfffe;

    push(registers, bus, registers.pc >> 8);
    push(registers, bus, registers.pc & 0xff);
    push(registers, bus, registers.p.toByte());

    registers.pc = IRQInterruptVector;
    registers.p.b = true;

    return 7;
}

//
// ORA
//

uint8_t ORAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{ 
    registers.a |= bus.read(indirectXAddr(registers, bus));

    registers.pc += 2;
    setNZ(registers, registers.a);
    return 6; 
}

uint8_t ORAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a |= bus.read(bus.read(registers.pc+1));
    registers.pc +=2;
    setNZ(registers, registers.a);
    return 3;
}

uint8_t ORAInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a |= bus.read(registers.pc+1);
    registers.pc +=2;
    setNZ(registers, registers.a);
    return 2;
}

uint8_t ORAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a |= bus.read(read16(bus, registers.pc + 1));
    registers.pc +=3;
    setNZ(registers, registers.a);
    return 4;
}

uint8_t ORAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{ 
    bool pageCrossed;
    registers.a |= bus.read(indirectYAddr(registers, bus, pageCrossed));
    registers.pc += 2;
    setNZ(registers, registers.a);
    return 5 + pageCrossed; 
}

uint8_t ORAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a |= bus.read(getZeroPageXYAddr(registers, bus, registers.x));
    registers.pc +=2;
    setNZ(registers, registers.a);
    return 4;
}

uint8_t ORAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool crossed;
    registers.a |= bus.read(getABSXYAddr(registers, bus, registers.y, crossed));
    registers.pc +=3;
    setNZ(registers, registers.a);
    return 4 + crossed;
}

uint8_t ORAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool crossed;
    registers.a |= bus.read(getABSXYAddr(registers, bus, registers.x, crossed));
    registers.pc +=3;
    setNZ(registers, registers.a);
    return 4 + crossed;
}

//
// ASL
//

uint8_t ASLInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = bus.read(registers.pc + 1);
    uint8_t value = bus.read(ptr);
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    bus.write(ptr, value);
    setNZ(registers, value);
    registers.pc += 3;
    return 5;
}

uint8_t ASLInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.p.c = (registers.a & 0x80) > 0;
    registers.a <<= 1;
    setNZ(registers, registers.a);
    return 2;
}

uint8_t ASLInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = read16(bus, registers.pc + 1);
    uint8_t value = bus.read(ptr);
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    bus.write(ptr, value);
    setNZ(registers, value);
    registers.pc += 3;
    return 6;
}
uint8_t ASLInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = getZeroPageXYAddr(registers, bus, registers.x);
    auto value = bus.read(ptr);
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    bus.write(ptr, value);
    setNZ(registers, value);
    registers.pc+= 2;
    return 6;
}

uint8_t ASLInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed; // unused
    auto ptr = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    auto value = bus.read(ptr);
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    bus.write(ptr, value);
    setNZ(registers, value);
    registers.pc+= 3;
    return 7;
}     

//
// PHP
//

uint8_t PHPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    push(registers, bus, registers.p.toByte());
    return 3;
}

//
// BPL
//

uint8_t BPLInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    if(registers.p.n)
    {
        registers.pc +=2;
        return 2;
    }

    auto jmp = static_cast<int8_t>(bus.read(registers.pc+1));
    auto page = registers.pc & 0xFF00;
    registers.pc += jmp;
    
    return 3 + (page != (registers.pc & 0xFF00));
}

//
// CLC
//

uint8_t CLCInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.p.c = false;
    return 2;
}       

//
// JSR
//

uint8_t JSRInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    push(registers, bus, (registers.pc + 2) >> 8);
    push(registers, bus, (registers.pc + 2) & 0xff);
    registers.pc = read16(bus, registers.pc + 1);
    return 6;
}

//
// AND
//

uint8_t ANDInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a &= bus.read(indirectXAddr(registers, bus));

    registers.pc += 2;
    setNZ(registers, registers.a);
    return 6; 
}
uint8_t ANDInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a &= bus.read(bus.read(registers.pc +1));
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 3; 
}

uint8_t ANDInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a &= bus.read(registers.pc +1);
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 2;
}

uint8_t ANDInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a &= bus.read(read16(bus, registers.pc +1));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4; 
}
uint8_t ANDInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a &= bus.read(indirectYAddr(registers, bus, pageCrossed));
    registers.pc += 2;
    setNZ(registers, registers.a);
    return 5 + pageCrossed; 
}
uint8_t ANDInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a &= bus.read(getZeroPageXYAddr(registers, bus, registers.x));
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 4; 
}
uint8_t ANDInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a &= bus.read(getABSXYAddr(registers, bus, registers.y, pageCrossed));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4 + pageCrossed;
}

uint8_t ANDInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a &= bus.read(getABSXYAddr(registers, bus, registers.x, pageCrossed));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4 + pageCrossed;
}

//
// BIT
//

uint8_t BITInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto value = bus.read(registers.pc + 1) & registers.a;
    setNZ(registers, value);
    registers.pc += 3;
    return 4;

}

uint8_t BITInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto value = read16(bus, registers.pc + 1) & registers.a;
    setNZ(registers, value);
    registers.pc += 3;
    return 4;
}

//
// ROL
//

uint8_t ROLInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr   = bus.read(registers.pc + 1);
    auto value = bus.read(ptr);

    registers.pc += 2;
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    value |= carry;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 5;
}

uint8_t ROLInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    registers.pc++;
    registers.p.c = (registers.a & 0x80) > 0;
    registers.a <<= 1;
    registers.a |= carry;
    setNZ(registers, registers.a);
    return 2;
}

uint8_t ROLInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr   = read16(bus, registers.pc +1);
    auto value = bus.read(ptr);

    registers.pc += 3;
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    value |= carry;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 6;
}

uint8_t ROLInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr = getZeroPageXYAddr(registers, bus, registers.x);
    auto value = bus.read(ptr);

    registers.pc += 2;
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    value |= carry;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 6;
}

uint8_t ROLInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    bool pageCrossed; // not used
    auto ptr = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    auto value = bus.read(ptr);

    registers.pc += 3;
    registers.p.c = (value & 0x80) > 0;
    value <<= 1;
    value |= carry;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 7;
}

//
// PLP
//

uint8_t PLPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.p.fromByte(pull(registers, bus));
    return 4;
}

//
// BMI
//

uint8_t BMIInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    if(!registers.p.n)
    {
        registers.pc +=2;
        return 2;
    }

    auto jmp = static_cast<int8_t>(bus.read(registers.pc+1));
    auto page = registers.pc & 0xFF00;
    registers.pc += jmp;
    
    return 3 + (page != (registers.pc & 0xFF00));
}

//
// SEC
//

uint8_t SECInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.p.c = true;
    return 2;
}     

//
// RTI
//

uint8_t RTIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto p   = pull(registers, bus);
    auto pcl = pull(registers, bus);
    auto pch = pull(registers, bus);

    registers.p.fromByte(p);
    registers.pc = (pch << 8) | pcl;

    return 6;
}

//
// EOR
//


uint8_t EORInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a ^= bus.read(indirectXAddr(registers, bus));

    registers.pc += 2;
    setNZ(registers, registers.a);
    return 6; 
}
uint8_t EORInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a ^= bus.read(bus.read(registers.pc +1));
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 3; 
}

uint8_t EORInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a ^= bus.read(registers.pc +1);
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 2;
}

uint8_t EORInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a ^= bus.read(read16(bus, registers.pc +1));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4; 
}
uint8_t EORInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a ^= bus.read(indirectYAddr(registers, bus, pageCrossed));
    registers.pc += 2;
    setNZ(registers, registers.a);
    return 5 + pageCrossed; 
}
uint8_t EORInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a ^= bus.read(getZeroPageXYAddr(registers, bus, registers.x));
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 4; 
}
uint8_t EORInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a ^= bus.read(getABSXYAddr(registers, bus, registers.y, pageCrossed));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4 + pageCrossed;
}

uint8_t EORInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a ^= bus.read(getABSXYAddr(registers, bus, registers.x, pageCrossed));
    setNZ(registers, registers.a);
    registers.pc += 3;
    return 4 + pageCrossed;
}
  

//
// LSR
//

uint8_t LSRInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    uint16_t ptr   = bus.read(registers.pc + 1);
    uint8_t  value = bus.read(ptr);
    registers.pc += 3;
    registers.p.c = value & 1;
    value >>= 1;
    registers.p.z = value == 0;
    registers.p.n = (value & 0x80) > 0; // do we really need this? this should never be possible.
    bus.write(ptr, value);
    return 5;
}
uint8_t LSRInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.p.c = registers.a & 1;
    registers.a >>= 1;
    registers.p.z = registers.a == 0;
    registers.p.n = (registers.a & 0x80) > 0; // do we really need this? this should never be possible.
    return 2;    
}

uint8_t LSRInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    uint16_t ptr   = read16(bus, registers.pc + 1);
    uint8_t  value = bus.read(ptr);
    registers.pc += 3;
    registers.p.c = value & 1;
    value >>= 1;
    registers.p.z = value == 0;
    registers.p.n = (value & 0x80) > 0; // do we really need this? this should never be possible.
    bus.write(ptr, value);
    return 6;
}

uint8_t LSRInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    uint16_t ptr   = getZeroPageXYAddr(registers, bus, registers.x);
    uint8_t  value = bus.read(ptr);
    registers.pc += 2;
    registers.p.c = value & 1;
    value >>= 1;
    registers.p.z = value == 0;
    registers.p.n = (value & 0x80) > 0; // do we really need this? this should never be possible.
    bus.write(ptr, value);
    return 6;
}

uint8_t LSRInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed; // not used
    uint16_t ptr   = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    uint8_t  value = bus.read(ptr);
    registers.pc += 3;
    registers.p.c = value & 1;
    value >>= 1;
    registers.p.z = value == 0;
    registers.p.n = (value & 0x80) > 0; // do we really need this? this should never be possible.
    bus.write(ptr, value);
    return 7;
}

//
// PHA
//

uint8_t PHAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    push(registers, bus, registers.a);
    return 3;
}

//
// JMP
//

uint8_t JMPInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    uint16_t addr = 0;
    addr |= bus.read(registers.pc+1);
    addr |= bus.read(registers.pc+2) << 8;
    registers.pc = addr;
    return 3;
}

uint8_t JMPInstruction::IABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    // indirect addressing (ABS)
    uint16_t addr = 0;
    addr |= bus.read(registers.pc+1);
    addr |= bus.read(registers.pc+2) << 8;
    registers.pc  = bus.read(addr);

    if((addr & 0xff) == 0xff)
    {   // quirk: see http://www.obelisk.me.uk/6502/reference.html#JMP
        registers.pc |= bus.read(addr & 0xFF00) << 8;
    }
    else
    {
        registers.pc |= bus.read(addr+1) << 8;
    }
    return 5;
}

//
// BVC
//

uint8_t BVCInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    if(registers.p.v)
    {
        registers.pc +=2;
        return 2;
    }

    auto page = registers.pc & 0xFF00;
    registers.pc += static_cast<int8_t>(bus.read(registers.pc+1));

    return 3 + (page != (registers.pc & 0xFF00));
}  

//
// CLI
//

uint8_t CLIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.p.i = false;
    return 2; 
}

//
// RTS
//

uint8_t RTSInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto pcl = pull(registers, bus);
    auto pch = pull(registers, bus);
    registers.pc = ((pch << 8) | pcl) - 1;
    return 6;
}

//
// ADC
//

// should we implement the decimal flag + 1 tick? NES doesn't use the decimal flag.

//http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
uint8_t ADCInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performADC(registers, bus, bus.read(indirectXAddr(registers, bus)));
    registers.pc += 2;
    return 6;
}

uint8_t ADCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performADC(registers, bus, bus.read(bus.read(registers.pc + 1)));
    registers.pc += 2;
    return 3;
}

uint8_t ADCInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performADC(registers, bus, bus.read(registers.pc + 1));
    registers.pc += 2;
    return 2;
}

uint8_t ADCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performADC(registers, bus, bus.read(read16(bus, registers.pc + 1)));
    registers.pc += 3;
    return 4;
}

uint8_t ADCInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performADC(registers, bus, bus.read(indirectYAddr(registers, bus, pageCrossed)));
    registers.pc += 2;
    return 5 + pageCrossed;
}

uint8_t ADCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performADC(registers, bus, bus.read(getZeroPageXYAddr(registers, bus, registers.x)));
    registers.pc += 2;
    return 4;
}

uint8_t ADCInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performADC(registers, bus, bus.read(getABSXYAddr(registers, bus, registers.y, pageCrossed)));
    registers.pc += 3;
    return 4 + pageCrossed;
}

uint8_t ADCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performADC(registers, bus, bus.read(getABSXYAddr(registers, bus, registers.x, pageCrossed)));
    registers.pc += 3;
    return 4 + pageCrossed;
}

//
// ROR
//

uint8_t RORInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr   = bus.read(registers.pc + 1);
    auto value = bus.read(ptr);

    registers.pc += 2;
    registers.p.c = value & 1;
    value >>= 1;
    value |= carry << 7;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 5;
}

uint8_t RORInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    registers.pc++;
    registers.p.c = registers.a & 1;
    registers.a >>= 1;
    registers.a |= carry << 7;
    setNZ(registers, registers.a);
    return 2;
}

uint8_t RORInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr   = read16(bus, registers.pc +1);
    auto value = bus.read(ptr);

    registers.pc += 3;
    registers.p.c = value & 1;
    value >>= 1;
    value |= carry << 7;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 6;
}

uint8_t RORInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    auto ptr = getZeroPageXYAddr(registers, bus, registers.x);
    auto value = bus.read(ptr);

    registers.pc += 2;
    registers.p.c = value & 1;
    value >>= 1;
    value |= carry << 7;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 6;
}

uint8_t RORInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto carry = registers.p.c;
    bool pageCrossed; // not used
    auto ptr = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    auto value = bus.read(ptr);

    registers.pc += 3;
    registers.p.c = value & 1;
    value >>= 1;
    value |= carry << 7;
    setNZ(registers, value);
    bus.write(ptr, value);
    return 7;
}


//
// PLA
//

uint8_t PLAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.a = pull(registers, bus);
    registers.p.n = (registers.a & 0x80) > 0;
    registers.p.z = registers.a == 0;
    return 4;
}

//
// BVS
//

uint8_t BVSInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SEI
//

uint8_t SEIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.p.i = true;
    return 2; 
}

//
// STA
//

uint8_t STAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bus.write(indirectXAddr(registers, bus), registers.a);
    registers.pc += 2;
    return 6;
}
uint8_t STAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZP(registers, bus, registers.a);
}
uint8_t STAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeABS(registers, bus, registers.a);
}

uint8_t STAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    bus.write(indirectYAddr(registers, bus, pageCrossed), registers.a);
    registers.pc += 2;
    return 6;
}
uint8_t STAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZPXY(registers, bus, registers.a, registers.x);
}

uint8_t STAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeABSXY(registers, bus, registers.a, registers.y);
}

uint8_t STAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeABSXY(registers, bus, registers.a, registers.x);
}

//
// STY
//

uint8_t STYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZP(registers, bus, registers.y);
}

uint8_t STYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeABS(registers, bus, registers.y);
}

uint8_t STYInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZPXY(registers, bus, registers.y, registers.x);
}

//
// STX
//

uint8_t STXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZP(registers, bus, registers.x);
}

uint8_t STXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeABS(registers, bus, registers.x);
}

uint8_t STXInstruction::ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return storeZPXY(registers, bus, registers.x, registers.y);
}

//
// DEY
//

uint8_t DEYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.y--;
    registers.p.z = registers.y == 0;
    registers.p.n = (registers.y & 0x80) > 0;
    return 2;
}     

//
// TXA
//

uint8_t TXAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.a = registers.x;
    registers.p.z = registers.a == 0;
    registers.p.n = (registers.a & 0x80) > 0;
    return 2;
}

//
// BCC
//

uint8_t BCCInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TYA
//

uint8_t TYAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.a = registers.y;
    registers.p.z = registers.a == 0;
    registers.p.n = (registers.a & 0x80) > 0;
    return 2;
}

//
// TXS
//

uint8_t TXSInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.sp = registers.x;
    return 2;
}

//
// LDY
//

uint8_t LDYInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetImmediate(registers, bus, registers.y);
}

uint8_t LDYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPage(registers, bus, registers.y);
}

uint8_t LDYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsolute(registers, bus, registers.y);
}

uint8_t LDYInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPageXY(registers, bus, registers.y, registers.x);
}

uint8_t LDYInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsoluteXY(registers, bus, registers.y, registers.x);    
}

//
// LDA
//

uint8_t LDAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.a = bus.read(indirectXAddr(registers, bus));
    setNZ(registers, registers.a);
    registers.pc +=2;
    return 6;
}

uint8_t LDAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPage(registers, bus, registers.a);
}

uint8_t LDAInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetImmediate(registers, bus, registers.a);
}

uint8_t LDAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsolute(registers, bus, registers.a);
}

uint8_t LDAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    registers.a = bus.read(indirectYAddr(registers, bus, pageCrossed));
    setNZ(registers, registers.a);
    registers.pc += 2;
    return 5 + pageCrossed;
}

uint8_t LDAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPageXY(registers, bus, registers.a, registers.x);
}

uint8_t LDAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsoluteXY(registers, bus, registers.a, registers.y);
}

uint8_t LDAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsoluteXY(registers, bus, registers.a, registers.x);
}


//
// LDX
//

uint8_t LDXInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetImmediate(registers, bus, registers.x);
}

uint8_t LDXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPage(registers, bus, registers.x);
}

uint8_t LDXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsolute(registers, bus, registers.x);
}

uint8_t LDXInstruction::ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetZeroPageXY(registers, bus, registers.x, registers.y);
}

uint8_t LDXInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    return ldTargetAbsoluteXY(registers, bus, registers.x, registers.y);
}

//
// TAY
//

uint8_t TAYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.y = registers.a;
    registers.p.z = registers.y == 0;
    registers.p.n = (registers.y & 0x80) > 0;
    return 2;
}

//
// TAX
//

uint8_t TAXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.x   = registers.a;
    registers.p.z = registers.x == 0;
    registers.p.n = (registers.x & 0x80) > 0;
    return 2;
}

//
// BCS
//

uint8_t BCSInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLV
//

uint8_t CLVInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.p.v = false;
    return 2; 
}

//
// TSX
//

uint8_t TSXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.x = registers.sp;
    registers.p.n = (registers.x & 0x80) > 0;
    registers.p.z = registers.x == 0;
    return 2;
}

//
// CPY
//

uint8_t CPYInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.y, bus.read(registers.pc + 1));
    registers.pc += 2;
    return 2;
}

uint8_t CPYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.y, bus.read(bus.read(registers.pc + 1)));
    registers.pc += 2;
    return 3;
}

uint8_t CPYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)      
{
    compare(registers, registers.y, bus.read(read16(bus, registers.pc + 1)));
    registers.pc += 3;
    return 4;
}
//
// CMP
//

uint8_t CMPInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.a, bus.read(indirectXAddr(registers, bus)));
    registers.pc += 2;
    return 6;

}

uint8_t CMPInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.a, bus.read(bus.read(registers.pc + 1)));
    registers.pc += 2;
    return 3;
}

uint8_t CMPInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.a, bus.read(registers.pc + 1));
    registers.pc += 2;
    return 2;
}

uint8_t CMPInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.a, bus.read(read16(bus, registers.pc + 1)));
    registers.pc += 3;
    return 4;
}

uint8_t CMPInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    compare(registers, registers.a, bus.read(indirectYAddr(registers, bus, pageCrossed)));
    registers.pc += 2;    
    return 5 + pageCrossed;
}

uint8_t CMPInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.a, bus.read(getZeroPageXYAddr(registers, bus, registers.x)));
    registers.pc += 2;
    return 4;
}

uint8_t CMPInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    compare(registers, registers.a, bus.read(getABSXYAddr(registers, bus, registers.y, pageCrossed)));
    registers.pc += 3;
    return 4 + pageCrossed;
}

uint8_t CMPInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    compare(registers, registers.a, bus.read(getABSXYAddr(registers, bus, registers.x, pageCrossed)));
    registers.pc += 3;
    return 4 + pageCrossed;
}

//
// DEC
//

uint8_t DECInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = bus.read(registers.pc + 1);
    auto value = bus.read(ptr);
    value--;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 2;
    return 5;
}

uint8_t DECInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = read16(bus, registers.pc + 1);
    auto value = bus.read(ptr);
    value--;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 3;
    return 6;
}

uint8_t DECInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = getZeroPageXYAddr(registers, bus, registers.x);
    auto value = bus.read(ptr);
    value--;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 2;
    return 6;
}

uint8_t DECInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed; // not used
    auto ptr = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    auto value = bus.read(ptr);
    value--;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 3;
    return 7;
} 

//
// INY
//

uint8_t INYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.y++;
    registers.p.z = registers.y == 0;
    registers.p.n = (registers.y & 0x80) > 0;
    return 2;
}

//
// DEX
//

uint8_t DEXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.x--;
    registers.p.z = registers.x == 0;
    registers.p.n = (registers.x & 0x80) > 0;
    return 2;
}

//
// BNE
//

uint8_t BNEInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLD
//

uint8_t CLDInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{ 
    registers.pc++;
    registers.p.d = false;
    return 2; 
}

//
// CPX
//

uint8_t CPXInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.x, bus.read(registers.pc + 1));
    registers.pc += 2;
    return 2;
}

uint8_t CPXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    compare(registers, registers.x, bus.read(bus.read(registers.pc + 1)));
    registers.pc += 2;
    return 3;
}

uint8_t CPXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)      
{
    compare(registers, registers.x, bus.read(read16(bus, registers.pc + 1)));
    registers.pc += 3;
    return 4;
}
//
// SBC
//

uint8_t SBCInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performSBC(registers, bus, bus.read(indirectXAddr(registers, bus)));
    registers.pc += 2;
    return 6;
}

uint8_t SBCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performSBC(registers, bus, bus.read(bus.read(registers.pc + 1)));
    registers.pc += 2;
    return 3;
}

uint8_t SBCInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    performSBC(registers, bus, bus.read(registers.pc + 1));
    registers.pc += 2;
    return 2;
}

uint8_t SBCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performSBC(registers, bus, bus.read(read16(bus, registers.pc + 1)));
    registers.pc += 3;
    return 4;
}

uint8_t SBCInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performSBC(registers, bus, bus.read(indirectYAddr(registers, bus, pageCrossed)));
    registers.pc += 2;
    return 5 + pageCrossed;
}

uint8_t SBCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    performSBC(registers, bus, getZeroPageXYAddr(registers, bus, registers.x));
    registers.pc += 2;
    return 4;
}

uint8_t SBCInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performSBC(registers, bus, getABSXYAddr(registers, bus, registers.y, pageCrossed));
    registers.pc += 3;
    return 4 + pageCrossed;
}

uint8_t SBCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed;
    performSBC(registers, bus, getABSXYAddr(registers, bus, registers.x, pageCrossed));
    registers.pc += 3;
    return 4 + pageCrossed;
}

//
// INC
//

uint8_t INCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = bus.read(registers.pc + 1);
    auto value = bus.read(ptr);
    value++;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 2;
    return 5;
}

uint8_t INCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = read16(bus, registers.pc + 1);
    auto value = bus.read(ptr);
    value++;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 3;
    return 6;
}

uint8_t INCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    auto ptr = getZeroPageXYAddr(registers, bus, registers.x);
    auto value = bus.read(ptr);
    value++;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 2;
    return 6;
}

uint8_t INCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    bool pageCrossed; // not used
    auto ptr = getABSXYAddr(registers, bus, registers.x, pageCrossed);
    auto value = bus.read(ptr);
    value++;
    bus.write(ptr, value);

    setNZ(registers, value);
    registers.pc += 3;
    return 7;
}

//
// INX
//

uint8_t INXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{
    registers.pc++;
    registers.x++;
    registers.p.z = registers.x == 0;
    registers.p.n = (registers.x & 0x80) > 0;
    return 2;
}

//
// NOP
//

uint8_t NOPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) 
{ 
    registers.pc++;
    return 1; 
}

//
// BEQ
//

uint8_t BEQInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SED
//

uint8_t SEDInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus)
{
    registers.pc++;
    registers.p.d = true;
    return 2;
}

}