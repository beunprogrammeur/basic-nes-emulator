#pragma once
#include <nes/cpu/registers.h>
#include <nes/cpu/instructions/base_instruction.h>
#include <nes/cpu/bus/ibus.h>
namespace nes::cpu::instructions
{
//
// Constructors
//

// Add memory to accumulator with carry
class ADCInstruction : public BaseInstruction
{
public:
    ADCInstruction(IInstructionErrorHandler& handler);
};

// "AND" memory with accumulator
class ANDInstruction : public BaseInstruction
{
public:
    ANDInstruction(IInstructionErrorHandler& handler);
};

// Shift left one bit (memory or accumulator)
class ASLInstruction : public BaseInstruction
{
public:
    ASLInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry clear
class BCCInstruction : public BaseInstruction
{
public:
    BCCInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry set
class BCSInstruction : public BaseInstruction
{
public:
    BCSInstruction(IInstructionErrorHandler& handler);
};

// Branch on result zero
class BEQInstruction : public BaseInstruction
{
public:
    BEQInstruction(IInstructionErrorHandler& handler);
};

// Test bits in memory with accumulator
class BITInstruction : public BaseInstruction
{
public:
    BITInstruction(IInstructionErrorHandler& handler);
};

// Branch on result minus
class BMIInstruction : public BaseInstruction
{
public:
    BMIInstruction(IInstructionErrorHandler& handler);
};

// Branch on result not zero
class BNEInstruction : public BaseInstruction
{
public:
    BNEInstruction(IInstructionErrorHandler& handler);
};

// Branch on result plus
class BPLInstruction : public BaseInstruction
{
public:
    BPLInstruction(IInstructionErrorHandler& handler);
};

// Force break
class BRKInstruction : public BaseInstruction
{
public:
    BRKInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow clear
class BVCInstruction : public BaseInstruction
{
public:
    BVCInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow set
class BVSInstruction : public BaseInstruction
{
public:
    BVSInstruction(IInstructionErrorHandler& handler);
};

// Clear carry flag
class CLCInstruction : public BaseInstruction
{
public:
    CLCInstruction(IInstructionErrorHandler& handler);
};

// Clear decimal mode
class CLDInstruction : public BaseInstruction
{
public:
    CLDInstruction(IInstructionErrorHandler& handler);
};

// Clear interrupt disable bit
class CLIInstruction : public BaseInstruction
{
public:
    CLIInstruction(IInstructionErrorHandler& handler);
};

// Clear overflow flag
class CLVInstruction : public BaseInstruction
{
public:
    CLVInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and accumulator
class CMPInstruction : public BaseInstruction
{
public:
    CMPInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index X
class CPXInstruction : public BaseInstruction
{
public:
    CPXInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index Y
class CPYInstruction : public BaseInstruction
{
public:
    CPYInstruction(IInstructionErrorHandler& handler);
};

// Decrement memory by one
class DECInstruction : public BaseInstruction
{
public:
    DECInstruction(IInstructionErrorHandler& handler);
};

// Decrement index X by one
class DEXInstruction : public BaseInstruction
{
public:
    DEXInstruction(IInstructionErrorHandler& handler);
};

// Decrement index Y by one
class DEYInstruction : public BaseInstruction
{
public:
    DEYInstruction(IInstructionErrorHandler& handler);
};

// "Exclusive or" memory with accumulator
class EORInstruction : public BaseInstruction
{
public:
    EORInstruction(IInstructionErrorHandler& handler);
};

// Increment memory by one
class INCInstruction : public BaseInstruction
{
public:
    INCInstruction(IInstructionErrorHandler& handler);
};

// Increment index X by one
class INXInstruction : public BaseInstruction
{
public:
    INXInstruction(IInstructionErrorHandler& handler);
};

// Increment index Y by one
class INYInstruction : public BaseInstruction
{
public:
    INYInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location
class JMPInstruction : public BaseInstruction
{
public:
    JMPInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location saving return address
class JSRInstruction : public BaseInstruction
{
public:
    JSRInstruction(IInstructionErrorHandler& handler);
};

// Load accumulator with memory
class LDAInstruction : public BaseInstruction
{
public:
    LDAInstruction(IInstructionErrorHandler& handler);
};

// Load index X with memory
class LDXInstruction : public BaseInstruction
{
public:
    LDXInstruction(IInstructionErrorHandler& handler);
};

// Load index y with memory
class LDYInstruction : public BaseInstruction
{
public:
    LDYInstruction(IInstructionErrorHandler& handler);
};

// Shift one bit right (memory or accumulator)
class LSRInstruction : public BaseInstruction
{
public:
    LSRInstruction(IInstructionErrorHandler& handler);
};

// No operation
class NOPInstruction : public BaseInstruction
{
public:
    NOPInstruction(IInstructionErrorHandler& handler);
};

// "OR" memory with accumulator
class ORAInstruction : public BaseInstruction
{
public:
    ORAInstruction(IInstructionErrorHandler& handler);
};

// Push accumulator on stack
class PHAInstruction : public BaseInstruction
{
public:
    PHAInstruction(IInstructionErrorHandler& handler);
};

// Push processor status on stack
class PHPInstruction : public BaseInstruction
{
public:
    PHPInstruction(IInstructionErrorHandler& handler);
};

// Pull accumulator from stack
class PLAInstruction : public BaseInstruction
{
public:
    PLAInstruction(IInstructionErrorHandler& handler);
};

// Pull processor status from stack
class PLPInstruction : public BaseInstruction
{
public:
    PLPInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit left (memory or accumulator)
class ROLInstruction : public BaseInstruction
{
public:
    ROLInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit right (memory or accumulator)
class RORInstruction : public BaseInstruction
{
public:
    RORInstruction(IInstructionErrorHandler& handler);
};

// Return from interrupt
class RTIInstruction : public BaseInstruction
{
public:
    RTIInstruction(IInstructionErrorHandler& handler);
};

// Return from subroutine
class RTSInstruction : public BaseInstruction
{
public:
    RTSInstruction(IInstructionErrorHandler& handler);
};

// Subtract memory from accumulator with borrow
class SBCInstruction : public BaseInstruction
{
public:
    SBCInstruction(IInstructionErrorHandler& handler);
};

// Set carry flag
class SECInstruction : public BaseInstruction
{
public:
    SECInstruction(IInstructionErrorHandler& handler);
};

// Set decimal mode
class SEDInstruction : public BaseInstruction
{
public:
    SEDInstruction(IInstructionErrorHandler& handler);
};

// Set interrupt disable status
class SEIInstruction : public BaseInstruction
{
public:
    SEIInstruction(IInstructionErrorHandler& handler);
};

// Store accumulator in memory
class STAInstruction : public BaseInstruction
{
public:
    STAInstruction(IInstructionErrorHandler& handler);
};

// Store index X in memory
class STXInstruction : public BaseInstruction
{
public:
    STXInstruction(IInstructionErrorHandler& handler);
};

// Store index Y in memory
class STYInstruction : public BaseInstruction
{
public:
    STYInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index X
class TAXInstruction : public BaseInstruction
{
public:
    TAXInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index Y
class TAYInstruction : public BaseInstruction
{
public:
    TAYInstruction(IInstructionErrorHandler& handler);
};

// Transfer stack pointer to index X
class TSXInstruction : public BaseInstruction
{
public:
    TSXInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to accumulator
class TXAInstruction : public BaseInstruction
{
public:
    TXAInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to stack register
class TXSInstruction : public BaseInstruction
{
public:
    TXSInstruction(IInstructionErrorHandler& handler);
};

// Transfer index Y to accumulator
class TYAInstruction : public BaseInstruction
{
public:
    TYAInstruction(IInstructionErrorHandler& handler);
};
}