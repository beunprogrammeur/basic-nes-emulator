#pragma once
#include <nes/cpu/instructions/iinstruction.h>

namespace nes::cpu::instructions
{
    class IInstructionSet
    {
        virtual IInstruction& get(const uint8_t index) = 0;
    };
}