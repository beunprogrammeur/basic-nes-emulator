#pragma once
#include <nes/cpu/instructions/iinstruction_decoder.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>
#include <nes/cpu/instructions/iinstruction.h>
#include <nes/cpu/instructions/instructionset.h>
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
    AddressingMode _modeMatrix[256];
};
}