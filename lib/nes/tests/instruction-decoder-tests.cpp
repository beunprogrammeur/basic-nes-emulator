#include <gtest/gtest.h>
#include <nes/cpu/instructions/instruction_decoder.h>
#include <nes/cpu/instructions/instructionset.h>
#include <nes/cpu/bus/ibus.h>
#include <nes/cpu/registers.h>

using namespace nes::cpu::instructions;
using namespace nes::cpu;

class MockInstructionErrorHandler : public IInstructionErrorHandler
{
private:
    bool _raised;
    AddressingMode _mode;
public:
    virtual void invalidMode(IInstruction& instruction, AddressingMode mode) override { _raised = true; _mode = mode; }
    void reset()                { _raised = false; }
    bool raised() const         { return _raised;  }
    AddressingMode mode() const { return _mode;    }
};

class MockBus : public nes::cpu::bus::IBus
{
private:
    static const int size = 0xffff;
    uint8_t _memory[size];
public:
    MockBus()                                                          { for(int i = 0; i < size; i++) _memory[i] = 0x77; } // never test againts 0x77. if that number is found the instruction is broken
    virtual uint8_t read(uint16_t address) const                       { return _memory[address];  }                        // or specific bus address is not inintialized properly
    virtual void    write(uint16_t address, uint8_t value)             { _memory[address] = value; }
    virtual void    connect(nes::peripherals::IPeripheral& peripheral) { /* not used */            }
};

class InstructionDecoderTestFixture : public testing::Test
{
protected:
    MockInstructionErrorHandler* handler;
    nes::cpu::instructions::InstructionDecoder* decoder;
    nes::cpu::instructions::InstructionSet* instructionSet;
    MockBus* bus;
    nes::cpu::Registers registers;
    void SetUp() override
    {
        handler        = new MockInstructionErrorHandler;
        bus            = new MockBus;
        instructionSet = new nes::cpu::instructions::InstructionSet(*handler);
        decoder        = new nes::cpu::instructions::InstructionDecoder(registers, *bus, *instructionSet);

        registers.reset();
    }

    void TearDown() override
    {
        delete handler;
        delete decoder;
        delete instructionSet;
        delete bus;

        handler        = nullptr;
        decoder        = nullptr;
        instructionSet = nullptr;
        bus            = nullptr;
    }

    // loads a binary into the bus and preps the program counter
    // NOTE: this is different from the instruction-tests 'load' 
    //       that one loads the params for the opcode, this loads the opcode itself as well
    void load(uint16_t startAddress, std::initializer_list<uint8_t> binary)
    {
        int i = 0;
        for(auto byte : binary)
        {
            bus->write(startAddress + i++, byte);
        }

        registers.pc = startAddress;
    }
};

TEST_F(InstructionDecoderTestFixture, NOPInstructionCalled)
{
    constexpr uint8_t nop = 0xEA;
    load(0xFF00, {nop});
    int oldPC = registers.pc;
    decoder->tick();
    EXPECT_EQ(oldPC + 1, registers.pc);
}

TEST_F(InstructionDecoderTestFixture, STAInstructionCalledAndDisabledTicking)
{
    // The instruction takes more than one tick. During those 'busy ticks' we dont want any changes in the PC
    // This one takes 3 ticks to complete.
    constexpr uint8_t sta_zp = 0x85;
    constexpr uint8_t nop    = 0xEA;
    load(0xFF00, {sta_zp, 0x03, nop}); // store accumulator on the zero page (address 0x03)
    registers.a = 0xBA;                // value to store
    int oldPC = registers.pc;

    decoder->tick();
    EXPECT_EQ(oldPC + 2, registers.pc);
    EXPECT_EQ(0xBA, bus->read(0x03));
    decoder->tick();
    EXPECT_EQ(oldPC + 2, registers.pc);
    decoder->tick();
    EXPECT_EQ(oldPC + 2, registers.pc);
    decoder->tick();
    EXPECT_EQ(oldPC + 3, registers.pc); // instruction finished. it just ran the nop instruction.


}