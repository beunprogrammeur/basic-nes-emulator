#include <nes/cpu/instructions/instruction_decoder.h>

namespace nes::cpu::instructions
{

InstructionDecoder::InstructionDecoder(cpu::Registers& registers, bus::IBus& bus, IInstructionSet& instructionSet)
    : _instructionSet(instructionSet)
    , _bus(bus)
    , _registers(registers)
    , _excessTicks(1)
{}

void InstructionDecoder::tick()
{
    if(--_excessTicks > 0) return;
    uint8_t opcode    = _bus.read(_registers.pc);
    auto& instruction = _instructionSet.get(opcode);

    _excessTicks += instruction.execute(_registers, _bus);
}

}
