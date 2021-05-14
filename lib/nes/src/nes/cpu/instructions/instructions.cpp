#include <nes/cpu/instructions/instructions.h>

namespace nes::cpu::instructions
{
// constructors
ADSInstruction::ADSInstruction(IInstructionErrorHandler& handler) : BaseInstruction::BaseInstruction("ADS", handler) {}
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
// ADS OpCodes
//

//
// AND OpCodes
//

//
// ASL OpCodes
//

//
// BCC OpCodes
//

//
// BCS OpCodes
//

//
// BEQ OpCodes
//

//
// BIT OpCodes
//

//
// BMI OpCodes
//

//
// BNE OpCodes
//

//
// BPL OpCodes
//

//
// BRK OpCodes
//

//
// BVC OpCodes
//

//
// BVS OpCodes
//

//
// CLC OpCodes
//

//
// CLD OpCodes
//

//
// CLI OpCodes
//

//
// CLV OpCodes
//

//
// CMP OpCodes
//

//
// CPX OpCodes
//

//
// CPY OpCodes
//

//
// DEC OpCodes
//

//
// DEX OpCodes
//

//
// DEY OpCodes
//

//
// EOR OpCodes
//

//
// INC OpCodes
//

//
// INX OpCodes
//

//
// INY OpCodes
//

//
// JMP OpCodes
//

//
// JSR OpCodes
//

//
// LDA OpCodes
//

//
// LDX OpCodes
//

//
// LDY OpCodes
//

//
// LSR OpCodes
//

//
// NOP OpCodes
//

//
// ORA OpCodes
//

//
// PHA OpCodes
//

//
// PHP OpCodes
//

//
// PLA OpCodes
//

//
// PLP OpCodes
//

//
// ROL OpCodes
//

//
// ROR OpCodes
//

//
// RTI OpCodes
//

//
// RTS OpCodes
//

//
// SBC OpCodes
//

//
// SEC OpCodes
//

//
// SED OpCodes
//

//
// SEI OpCodes
//

//
// STA OpCodes
//

//
// STX OpCodes
//

//
// STY OpCodes
//

//
// TAX OpCodes
//

//
// TAY OpCodes
//

//
// TSX OpCodes
//

//
// TXA OpCodes
//

//
// TXS OpCodes
//

//
// TYA OpCodes
//


}