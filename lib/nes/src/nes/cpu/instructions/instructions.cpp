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

uint8_t BRKInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// ORA
//

uint8_t ORAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ORAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// ASL
//

uint8_t ASLInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ASLInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ASLInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ASLInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ASLInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// PHP
//

uint8_t PHPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BPL
//

uint8_t BPLInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLC
//

uint8_t CLCInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// JSR
//

uint8_t JSRInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// AND
//

uint8_t ANDInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ANDInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BIT
//

uint8_t BITInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t BITInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// ROL
//

uint8_t ROLInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ROLInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ROLInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ROLInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ROLInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// PLP
//

uint8_t PLPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BMI
//

uint8_t BMIInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SEC
//

uint8_t SECInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// RTI
//

uint8_t RTIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// EOR
//

uint8_t EORInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t EORInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// LSR
//

uint8_t LSRInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LSRInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LSRInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LSRInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LSRInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// PHA
//

uint8_t PHAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// JMP
//

uint8_t JMPInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t JMPInstruction::IABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BVC
//

uint8_t BVCInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLI
//

uint8_t CLIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// RTS
//

uint8_t RTSInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// ADC
//

uint8_t ADCInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t ADCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// ROR
//

uint8_t RORInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t RORInstruction::ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t RORInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t RORInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t RORInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// PLA
//

uint8_t PLAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BVS
//

uint8_t BVSInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SEI
//

uint8_t SEIInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// STA
//

uint8_t STAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// STY
//

uint8_t STYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STYInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// STX
//

uint8_t STXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t STXInstruction::ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// DEY
//

uint8_t DEYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TXA
//

uint8_t TXAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BCC
//

uint8_t BCCInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TYA
//

uint8_t TYAInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TXS
//

uint8_t TXSInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// LDY
//

uint8_t LDYInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDYInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDYInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// LDA
//

uint8_t LDAInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDAInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// LDX
//

uint8_t LDXInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDXInstruction::ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t LDXInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TAY
//

uint8_t TAYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TAX
//

uint8_t TAXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BCS
//

uint8_t BCSInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLV
//

uint8_t CLVInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// TSX
//

uint8_t TSXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CPY
//

uint8_t CPYInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CPYInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CPYInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CMP
//

uint8_t CMPInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CMPInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// DEC
//

uint8_t DECInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t DECInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t DECInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t DECInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// INY
//

uint8_t INYInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// DEX
//

uint8_t DEXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BNE
//

uint8_t BNEInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CLD
//

uint8_t CLDInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// CPX
//

uint8_t CPXInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CPXInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t CPXInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SBC
//

uint8_t SBCInstruction::IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t SBCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// INC
//

uint8_t INCInstruction::ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t INCInstruction::ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t INCInstruction::ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       
uint8_t INCInstruction::ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// INX
//

uint8_t INXInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// NOP
//

uint8_t NOPInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// BEQ
//

uint8_t BEQInstruction::REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

//
// SED
//

uint8_t SEDInstruction::IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) { return 0; }       

}