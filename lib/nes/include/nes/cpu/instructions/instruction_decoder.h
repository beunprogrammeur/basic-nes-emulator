#pragma once
#include <nes/cpu/instructions/iinstruction_decoder.h>
#include <nes/cpu/registers.h>
#include <nes/cpu/instructions/iinstruction.h>
#include <nes/cpu/instructions/instructionset.h>
#include <nes/cpu/bus/ibus.h>
#include <nes/cpu/clock/iclock_sink.h>

namespace nes::cpu::instructions
{

class InstructionDecoder : public IInstructionDecoder, public clock::IClockSink
{
private:
    IInstructionSet& _instructionSet;
    bus::IBus& _bus;
    cpu::Registers& _registers;
    int _excessTicks;    
public:
    InstructionDecoder(cpu::Registers& registers, bus::IBus& bus, IInstructionSet& instructionSet);
    virtual void tick() override;
};
}