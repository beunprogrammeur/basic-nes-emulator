#pragma once
#include <nes/cpu/instructions/iinstruction.h>

namespace nes::cpu::instructions
{

class IInstructionErrorHandler
{
public:
    virtual void invalidMode(IInstruction& instruction, AddressingMode mode) = 0;
};

}