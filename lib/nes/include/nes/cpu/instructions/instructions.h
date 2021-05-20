#pragma once
#include <nes/cpu/registers.h>
#include <nes/cpu/instructions/base_instruction.h>
#include <nes/cpu/bus/ibus.h>
namespace nes::cpu::instructions
{
// Force break
class BRKInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BRKInstruction(IInstructionErrorHandler& handler);
};

// 'OR' memory with accumulator
class ORAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    ORAInstruction(IInstructionErrorHandler& handler);
};

// Shift left one bit (memory or accumulator)
class ASLInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    ASLInstruction(IInstructionErrorHandler& handler);
};

// Push processor status on stack
class PHPInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    PHPInstruction(IInstructionErrorHandler& handler);
};

// Branch on result plus
class BPLInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BPLInstruction(IInstructionErrorHandler& handler);
};

// Clear carry flag
class CLCInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CLCInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location saving return address
class JSRInstruction : public BaseInstruction
{
private:
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    JSRInstruction(IInstructionErrorHandler& handler);
};

// 'AND' memory with accumulator
class ANDInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    ANDInstruction(IInstructionErrorHandler& handler);
};

// Test bits in memory with accumulator
class BITInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BITInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit left (memory or accumulator)
class ROLInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    ROLInstruction(IInstructionErrorHandler& handler);
};

// Pull processor status from stack
class PLPInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    PLPInstruction(IInstructionErrorHandler& handler);
};

// Branch on result minus
class BMIInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BMIInstruction(IInstructionErrorHandler& handler);
};

// Set carry flag
class SECInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    SECInstruction(IInstructionErrorHandler& handler);
};

// Return from interrupt
class RTIInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    RTIInstruction(IInstructionErrorHandler& handler);
};

// 'Exclusive or' memory with accumulator
class EORInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    EORInstruction(IInstructionErrorHandler& handler);
};

// Shift one bit right (memory or accumulator)
class LSRInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    LSRInstruction(IInstructionErrorHandler& handler);
};

// Push accumulator on stack
class PHAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    PHAInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location
class JMPInstruction : public BaseInstruction
{
private:
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    JMPInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow clear
class BVCInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BVCInstruction(IInstructionErrorHandler& handler);
};

// Clear interrupt disable bit
class CLIInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CLIInstruction(IInstructionErrorHandler& handler);
};

// Return from subroutine
class RTSInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    RTSInstruction(IInstructionErrorHandler& handler);
};

// Add memory to accumulator with carry
class ADCInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    ADCInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit right (memory or accumulator)
class RORInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ACC(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    RORInstruction(IInstructionErrorHandler& handler);
};

// Pull accumulator from stack
class PLAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    PLAInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow set
class BVSInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BVSInstruction(IInstructionErrorHandler& handler);
};

// Set interrupt disable status
class SEIInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    SEIInstruction(IInstructionErrorHandler& handler);
};

// Store accumulator in memory
class STAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    STAInstruction(IInstructionErrorHandler& handler);
};

// Store index Y in memory
class STYInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    STYInstruction(IInstructionErrorHandler& handler);
};

// Store index X in memory
class STXInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    STXInstruction(IInstructionErrorHandler& handler);
};

// Decrement index Y by one
class DEYInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    DEYInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to accumulator
class TXAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TXAInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry clear
class BCCInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BCCInstruction(IInstructionErrorHandler& handler);
};

// Transfer index Y to accumulator
class TYAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TYAInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to stack register
class TXSInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TXSInstruction(IInstructionErrorHandler& handler);
};

// Load index y with memory
class LDYInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    LDYInstruction(IInstructionErrorHandler& handler);
};

// Load accumulator with memory
class LDAInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    LDAInstruction(IInstructionErrorHandler& handler);
};

// Load index X with memory
class LDXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    LDXInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index Y
class TAYInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TAYInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index X
class TAXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TAXInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry set
class BCSInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BCSInstruction(IInstructionErrorHandler& handler);
};

// Clear overflow flag
class CLVInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CLVInstruction(IInstructionErrorHandler& handler);
};

// Transfer stack pointer to index X
class TSXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    TSXInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index Y
class CPYInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CPYInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and accumulator
class CMPInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CMPInstruction(IInstructionErrorHandler& handler);
};

// Decrement memory by one
class DECInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    DECInstruction(IInstructionErrorHandler& handler);
};

// Increment index Y by one
class INYInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    INYInstruction(IInstructionErrorHandler& handler);
};

// Decrement index X by one
class DEXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    DEXInstruction(IInstructionErrorHandler& handler);
};

// Branch on result not zero
class BNEInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BNEInstruction(IInstructionErrorHandler& handler);
};

// Clear decimal mode
class CLDInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CLDInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index X
class CPXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    CPXInstruction(IInstructionErrorHandler& handler);
};

// Subtract memory from accumulator with borrow
class SBCInstruction : public BaseInstruction
{
private:
    virtual uint8_t IINDX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IMM(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t IINDY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSY(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    SBCInstruction(IInstructionErrorHandler& handler);
};

// Increment memory by one
class INCInstruction : public BaseInstruction
{
private:
    virtual uint8_t ZP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABS(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ZPX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;
    virtual uint8_t ABSX(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    INCInstruction(IInstructionErrorHandler& handler);
};

// Increment index X by one
class INXInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    INXInstruction(IInstructionErrorHandler& handler);
};

// No operation
class NOPInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    NOPInstruction(IInstructionErrorHandler& handler);
};

// Branch on result zero
class BEQInstruction : public BaseInstruction
{
private:
    virtual uint8_t REL(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    BEQInstruction(IInstructionErrorHandler& handler);
};

// Set decimal mode
class SEDInstruction : public BaseInstruction
{
private:
    virtual uint8_t IMP(nes::cpu::Registers& registers, nes::cpu::bus::IBus& bus) override;

public:
    SEDInstruction(IInstructionErrorHandler& handler);
};

}