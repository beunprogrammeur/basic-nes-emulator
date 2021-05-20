#include <gtest/gtest.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>
#include <nes/cpu/instructions/instructions.h>
#include <nes/cpu/bus/ibus.h>
#include <nes/cpu/registers.h>
#include <vector>
#include <nes/cpu/instructions/instructionset.h>




using namespace nes::cpu::instructions;
using namespace nes::cpu;

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
    nes::cpu::Registers registers;
    void SetUp() override
    {
        handler = new MockInstructionErrorHandler;
        bus     = new MockBus(100);

        registers.reset();
    }

    void TearDown() override
    {
        delete handler;
        delete bus;

        handler = nullptr;
        bus     = nullptr;
    }
};



// based on information found here: http://www.obelisk.me.uk/6502/reference.html

TEST_F(InstructionTestFixture, NOPTest)
{
    NOPInstruction instruction(*handler);
    instruction.setMode(AddressingMode::IMP);

    auto expected = registers;
    expected.pc++;
    auto ticks = instruction.execute(registers, *bus);

    ASSERT_EQ(1, ticks);
    ASSERT_EQ(expected, registers);
    ASSERT_FALSE(handler->raised());
    
}

TEST_F(InstructionTestFixture, CLCTest)
{
    CLCInstruction instruction(*handler);
    instruction.setMode(AddressingMode::IMP);

    registers.p.c = true;
    auto expected = registers;
    expected.pc++;
    expected.p.c = false;
    
    auto ticks = instruction.execute(registers, *bus);

    ASSERT_EQ(2, ticks);
    ASSERT_EQ(expected, registers);
    ASSERT_FALSE(handler->raised());
}

TEST_F(InstructionTestFixture, CLDTest)
{
    CLDInstruction instruction(*handler);
    instruction.setMode(AddressingMode::IMP);

    registers.p.d = true;
    auto expected = registers;
    expected.pc++;
    expected.p.d = false;
    
    auto ticks = instruction.execute(registers, *bus);

    ASSERT_EQ(2, ticks);
    ASSERT_EQ(expected, registers);
    ASSERT_FALSE(handler->raised());
}

TEST_F(InstructionTestFixture, BRKTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ORATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, XXXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ASLTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, PHPTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BPLTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, JSRTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ANDTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BITTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ROLTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, PLPTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BMITest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, SECTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, RTITest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, EORTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, LSRTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, PHATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, JMPTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BVCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CLITest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, RTSTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ADCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, RORTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, PLATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BVSTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, SEITest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, STATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, STYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, STXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, DEYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TXATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BCCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TYATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TXSTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, LDYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, LDATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, LDXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TAYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TAXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BCSTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CLVTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TSXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CPYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CMPTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, DECTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, INYTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, DEXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BNETest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CPXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, SBCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, INCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, INXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, BEQTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, SEDTest)
{
    FAIL() << "Not yet implemented";
}