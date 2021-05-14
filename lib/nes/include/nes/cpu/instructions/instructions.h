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
class ADSInstruction : BaseInstruction
{
public:
    ADSInstruction(IInstructionErrorHandler& handler);
};

// "AND" memory with accumulator
class ANDInstruction : BaseInstruction
{
public:
    ANDInstruction(IInstructionErrorHandler& handler);
};

// Shift left one bit (memory or accumulator)
class ASLInstruction : BaseInstruction
{
public:
    ASLInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry clear
class BCCInstruction : BaseInstruction
{
public:
    BCCInstruction(IInstructionErrorHandler& handler);
};

// Branch on carry set
class BCSInstruction : BaseInstruction
{
public:
    BCSInstruction(IInstructionErrorHandler& handler);
};

// Branch on result zero
class BEQInstruction : BaseInstruction
{
public:
    BEQInstruction(IInstructionErrorHandler& handler);
};

// Test bits in memory with accumulator
class BITInstruction : BaseInstruction
{
public:
    BITInstruction(IInstructionErrorHandler& handler);
};

// Branch on result minus
class BMIInstruction : BaseInstruction
{
public:
    BMIInstruction(IInstructionErrorHandler& handler);
};

// Branch on result not zero
class BNEInstruction : BaseInstruction
{
public:
    BNEInstruction(IInstructionErrorHandler& handler);
};

// Branch on result plus
class BPLInstruction : BaseInstruction
{
public:
    BPLInstruction(IInstructionErrorHandler& handler);
};

// Force break
class BRKInstruction : BaseInstruction
{
public:
    BRKInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow clear
class BVCInstruction : BaseInstruction
{
public:
    BVCInstruction(IInstructionErrorHandler& handler);
};

// Branch on overflow set
class BVSInstruction : BaseInstruction
{
public:
    BVSInstruction(IInstructionErrorHandler& handler);
};

// Clear carry flag
class CLCInstruction : BaseInstruction
{
public:
    CLCInstruction(IInstructionErrorHandler& handler);
};

// Clear decimal mode
class CLDInstruction : BaseInstruction
{
public:
    CLDInstruction(IInstructionErrorHandler& handler);
};

// Clear interrupt disable bit
class CLIInstruction : BaseInstruction
{
public:
    CLIInstruction(IInstructionErrorHandler& handler);
};

// Clear overflow flag
class CLVInstruction : BaseInstruction
{
public:
    CLVInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and accumulator
class CMPInstruction : BaseInstruction
{
public:
    CMPInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index X
class CPXInstruction : BaseInstruction
{
public:
    CPXInstruction(IInstructionErrorHandler& handler);
};

// Compare memory and index Y
class CPYInstruction : BaseInstruction
{
public:
    CPYInstruction(IInstructionErrorHandler& handler);
};

// Decrement memory by one
class DECInstruction : BaseInstruction
{
public:
    DECInstruction(IInstructionErrorHandler& handler);
};

// Decrement index X by one
class DEXInstruction : BaseInstruction
{
public:
    DEXInstruction(IInstructionErrorHandler& handler);
};

// Decrement index Y by one
class DEYInstruction : BaseInstruction
{
public:
    DEYInstruction(IInstructionErrorHandler& handler);
};

// "Exclusive or" memory with accumulator
class EORInstruction : BaseInstruction
{
public:
    EORInstruction(IInstructionErrorHandler& handler);
};

// Increment memory by one
class INCInstruction : BaseInstruction
{
public:
    INCInstruction(IInstructionErrorHandler& handler);
};

// Increment index X by one
class INXInstruction : BaseInstruction
{
public:
    INXInstruction(IInstructionErrorHandler& handler);
};

// Increment index Y by one
class INYInstruction : BaseInstruction
{
public:
    INYInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location
class JMPInstruction : BaseInstruction
{
public:
    JMPInstruction(IInstructionErrorHandler& handler);
};

// Jump to new location saving return address
class JSRInstruction : BaseInstruction
{
public:
    JSRInstruction(IInstructionErrorHandler& handler);
};

// Load accumulator with memory
class LDAInstruction : BaseInstruction
{
public:
    LDAInstruction(IInstructionErrorHandler& handler);
};

// Load index X with memory
class LDXInstruction : BaseInstruction
{
public:
    LDXInstruction(IInstructionErrorHandler& handler);
};

// Load index y with memory
class LDYInstruction : BaseInstruction
{
public:
    LDYInstruction(IInstructionErrorHandler& handler);
};

// Shift one bit right (memory or accumulator)
class LSRInstruction : BaseInstruction
{
public:
    LSRInstruction(IInstructionErrorHandler& handler);
};

// No operation
class NOPInstruction : BaseInstruction
{
public:
    NOPInstruction(IInstructionErrorHandler& handler);
};

// "OR" memory with accumulator
class ORAInstruction : BaseInstruction
{
public:
    ORAInstruction(IInstructionErrorHandler& handler);
};

// Push accumulator on stack
class PHAInstruction : BaseInstruction
{
public:
    PHAInstruction(IInstructionErrorHandler& handler);
};

// Push processor status on stack
class PHPInstruction : BaseInstruction
{
public:
    PHPInstruction(IInstructionErrorHandler& handler);
};

// Pull accumulator from stack
class PLAInstruction : BaseInstruction
{
public:
    PLAInstruction(IInstructionErrorHandler& handler);
};

// Pull processor status from stack
class PLPInstruction : BaseInstruction
{
public:
    PLPInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit left (memory or accumulator)
class ROLInstruction : BaseInstruction
{
public:
    ROLInstruction(IInstructionErrorHandler& handler);
};

// Rotate one bit right (memory or accumulator)
class RORInstruction : BaseInstruction
{
public:
    RORInstruction(IInstructionErrorHandler& handler);
};

// Return from interrupt
class RTIInstruction : BaseInstruction
{
public:
    RTIInstruction(IInstructionErrorHandler& handler);
};

// Return from subroutine
class RTSInstruction : BaseInstruction
{
public:
    RTSInstruction(IInstructionErrorHandler& handler);
};

// Subtract memory from accumulator with borrow
class SBCInstruction : BaseInstruction
{
public:
    SBCInstruction(IInstructionErrorHandler& handler);
};

// Set carry flag
class SECInstruction : BaseInstruction
{
public:
    SECInstruction(IInstructionErrorHandler& handler);
};

// Set decimal mode
class SEDInstruction : BaseInstruction
{
public:
    SEDInstruction(IInstructionErrorHandler& handler);
};

// Set interrupt disable status
class SEIInstruction : BaseInstruction
{
public:
    SEIInstruction(IInstructionErrorHandler& handler);
};

// Store accumulator in memory
class STAInstruction : BaseInstruction
{
public:
    STAInstruction(IInstructionErrorHandler& handler);
};

// Store index X in memory
class STXInstruction : BaseInstruction
{
public:
    STXInstruction(IInstructionErrorHandler& handler);
};

// Store index Y in memory
class STYInstruction : BaseInstruction
{
public:
    STYInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index X
class TAXInstruction : BaseInstruction
{
public:
    TAXInstruction(IInstructionErrorHandler& handler);
};

// Transfer accumulator to index Y
class TAYInstruction : BaseInstruction
{
public:
    TAYInstruction(IInstructionErrorHandler& handler);
};

// Transfer stack pointer to index X
class TSXInstruction : BaseInstruction
{
public:
    TSXInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to accumulator
class TXAInstruction : BaseInstruction
{
public:
    TXAInstruction(IInstructionErrorHandler& handler);
};

// Transfer index X to stack register
class TXSInstruction : BaseInstruction
{
public:
    TXSInstruction(IInstructionErrorHandler& handler);
};

// Transfer index Y to accumulator
class TYAInstruction : BaseInstruction
{
public:
    TYAInstruction(IInstructionErrorHandler& handler);
};

//
// OpCode implementations
//



}