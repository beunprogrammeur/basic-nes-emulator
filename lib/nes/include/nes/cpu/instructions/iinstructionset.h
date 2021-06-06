#pragma once
#include <nes/cpu/instructions/iinstruction.h>

namespace nes::cpu::instructions
{
    class IInstructionSet
    {
    public:
        virtual IInstruction& get(const uint8_t index) = 0;
    };
}