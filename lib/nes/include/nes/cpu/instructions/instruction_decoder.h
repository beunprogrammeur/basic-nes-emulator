#pragma once
#include <nes/cpu/instructions/iinstruction_decoder.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>
#include <nes/cpu/instructions/iinstruction.h>
#include <nes/cpu/instructions/instructionset.h>
#include <nes/cpu/bus/ibus.h>

namespace nes::cpu::instructions
{

class TempHandler : public IInstructionErrorHandler
{
public:
    virtual void invalidMode(IInstruction& instruction, AddressingMode mode) override { }
};




    
class InstructionDecoder : public IInstructionDecoder
{
private:
    IInstructionSet& _instructionSet;
    bus::IBus& _bus;
    Registers& _registers;    
public:
    // TODO: interact with the (to be defined) oscillator
    // Add this to the IInstructionDecoder interface.
};
}