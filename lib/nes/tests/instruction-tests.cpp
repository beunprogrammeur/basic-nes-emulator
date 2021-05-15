#include <gtest/gtest.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>
#include <nes/cpu/instructions/instructions.h>
#include <nes/cpu/bus/ibus.h>
#include <nes/cpu/registers.h>
#include <vector>

using namespace nes::cpu::instructions;

// Definition of mock types

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
    std::vector<uint8_t> _memory;
public:
    MockBus(int size) : _memory(size)                                  { _memory.reserve(size); for(int i = 0; i < size; i++) _memory[i] = 0; }
    virtual uint8_t read(uint16_t address) const                       { return _memory[address];  }
    virtual void    write(uint16_t address, uint8_t value)             { _memory[address] = value; }
    virtual void    connect(nes::peripherals::IPeripheral& peripheral) { /* not used */            }
};

// Definition of test fixture

class InstructionTestFixture : public testing::Test
{
protected:
    MockInstructionErrorHandler* handler;
    MockBus* bus;
    void SetUp() override
    {
        handler = new MockInstructionErrorHandler;
        bus = new MockBus(100);
    }

    void TearDown() override
    {
        delete handler;
        delete bus;

        handler = nullptr;
        bus     = nullptr;
    }
};

TEST_F(InstructionTestFixture, NOPTest)
{
    ASSERT_EQ(1, 1);
}