#include <gtest/gtest.h>
#include <nes/cpu/instructions/iinstruction_error_handler.h>
#include <nes/cpu/instructions/instructions.h>
#include <nes/cpu/bus/ibus.h>
#include <nes/cpu/registers.h>
#include <vector>
#include <nes/cpu/instructions/instructionset.h>

#include <type_traits>
#include <sstream>

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
    static const int size = 0xffff;
    uint8_t _memory[size];
public:
    MockBus()                                                          { for(int i = 0; i < size; i++) _memory[i] = 0; }
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
        bus     = new MockBus;

        registers.reset();

        hex(0x1234);
    }

    void TearDown() override
    {
        delete handler;
        delete bus;

        handler = nullptr;
        bus     = nullptr;
    }

    template<typename T>
    std::string hex(T number)
    {
        std::stringstream ss;
        ss << "0x";
        constexpr char hx[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

        for(int i = 1; i <= sizeof(T) * 2; i++)
        {
            ss << hx[number >> ((sizeof(T) * 2 - 1) * 4)];
            number <<= 4;
        }

        return ss.str();
    }

    void compare(const nes::cpu::Registers& expected)
    {
        EXPECT_EQ(expected.a  , registers.a  ) << "expected accumulator to be "     << hex(expected.a  ) << " but it was " << hex(registers.a  );
        EXPECT_EQ(expected.x  , registers.x  ) << "expected index x to be "         << hex(expected.x  ) << " but it was " << hex(registers.x  );
        EXPECT_EQ(expected.y  , registers.y  ) << "expected index y to be "         << hex(expected.y  ) << " but it was " << hex(registers.y  );
        EXPECT_EQ(expected.pc , registers.pc ) << "expected program counter to be " << hex(expected.pc ) << " but it was " << hex(registers.pc );
        EXPECT_EQ(expected.sp , registers.sp ) << "expected stack pointer to be "   << hex(expected.sp ) << " but it was " << hex(registers.sp );
        EXPECT_EQ(expected.p.n, registers.p.n) << "expected negative flag to be "   << hex(expected.p.n) << " but it was " << hex(registers.p.n);
        EXPECT_EQ(expected.p.u, registers.p.u) << "expected unused flag to be "     << hex(expected.p.u) << " but it was " << hex(registers.p.u);
        EXPECT_EQ(expected.p.v, registers.p.v) << "expected overflow flag to be "   << hex(expected.p.v) << " but it was " << hex(registers.p.v);
        EXPECT_EQ(expected.p.b, registers.p.b) << "expected break flag to be "      << hex(expected.p.b) << " but it was " << hex(registers.p.b);
        EXPECT_EQ(expected.p.d, registers.p.d) << "expected decimal flag to be "    << hex(expected.p.d) << " but it was " << hex(registers.p.d);
        EXPECT_EQ(expected.p.i, registers.p.i) << "expected IRQ flag to be "        << hex(expected.p.i) << " but it was " << hex(registers.p.i);
        EXPECT_EQ(expected.p.z, registers.p.z) << "expected zero flag to be "       << hex(expected.p.z) << " but it was " << hex(registers.p.z);
        EXPECT_EQ(expected.p.c, registers.p.c) << "expected carry flag to be "      << hex(expected.p.c) << " but it was " << hex(registers.p.c);
    }

    void execute(IInstruction& instruction, int expectedTicks, bool handlerCalled = false)
    {
        EXPECT_EQ(expectedTicks, instruction.execute(registers, *bus));
        EXPECT_EQ(handlerCalled, handler->raised());
    }

    template<typename T>
    void run(AddressingMode mode, int ticks, Registers& expected, bool handlerCalled = false)
    {
        static_assert(std::is_base_of<IInstruction, T>::value, "T must be derived of IInstruction");
        auto instruction = T(*handler);
        instruction.setMode(mode);

        execute(instruction, ticks, handlerCalled);
        compare(expected);
    }

    // loads a binary into the bus and preps the program counter
    void load(std::initializer_list<uint8_t> binary)
    {
        constexpr uint16_t binaryStart = 0x0300; // chosen at random

        int i = 0;
        for(auto byte : binary)
        {
            bus->write(binaryStart + i++, byte);
        }

        registers.pc = binaryStart;
    }

    // stack value should be reverse order. newest stack entry first. 
    void stackcmp(std::initializer_list<uint8_t> stack)
    {
        auto sp = registers.sp;
        for(auto expected : stack)
        {
            auto actual = bus->read(0x0100 | ++sp);
            EXPECT_EQ(expected, actual) << "Expected stack value at " << hex(sp) << " to be " << hex(expected) << " but was " << hex(actual);
        }
    }

    uint8_t lo(uint16_t value)
    {
        return static_cast<uint8_t>(value & 0xff);
    }

    uint8_t hi(uint16_t value)
    {
        return static_cast<uint8_t>(value >> 8);
    }
};



// based on information found here: http://www.obelisk.me.uk/6502/reference.html

TEST_F(InstructionTestFixture, NOPTest)
{
    auto expected = registers;
    expected.pc++;
    run<NOPInstruction>(AddressingMode::IMP, 1, expected);
}

TEST_F(InstructionTestFixture, CLCTest)
{
    registers.p.c = true;
    auto expected = registers;
    expected.pc++;
    expected.p.c = false;
    run<CLCInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, CLDTest)
{
    registers.p.d = true;
    auto expected = registers;
    expected.pc++;
    expected.p.d = false;
    run<CLDInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, BRKTest)
{
    registers.pc = 0xABBA; // a number that we can identify the first and second byte order with.
    registers.p.c = true; // set some flags that we want to read back from the stack.
    registers.p.n = true; 

    auto expected = registers;
    expected.p.b = true;
    expected.pc = 0xfffe; // IRQ vector
    expected.sp -= 3;

    run<BRKInstruction>(AddressingMode::IMP, 7, expected);

    expected.p.b = false; // this one is set after it enters the stack. so it should be fase for the stack comparison
    expected.pc = 0xABBA; // same for the PC

    stackcmp({ // we check in reverse order
        expected.p.toByte(),
        hi(expected.pc),
        lo(expected.pc)
    });
}

TEST_F(InstructionTestFixture, ORATest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, XXXTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, ASLAccumulatorTest)
{
    registers.a = 0;
    auto expected = registers;
    expected.pc++;
    expected.p.z = true;
    run<ASLInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 10;
    expected = registers;
    expected.pc++;
    expected.a <<= 1;
    expected.p.z = false;
    run<ASLInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 64;
    expected = registers;
    expected.pc++;
    expected.a <<= 1;
    expected.p.n = true;
    run<ASLInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 129;
    expected = registers;
    expected.pc++;
    expected.a = 2;
    expected.p.c = true;
    expected.p.n = false;
    run<ASLInstruction>(AddressingMode::ACC, 2, expected);
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
    registers.a = 0x01;
    auto expected = registers;
    expected.pc++;
    expected.a <<= 1;
    run<ROLInstruction>(AddressingMode::ACC, 2, expected);

    registers.p.c = true;
    expected = registers;
    expected.pc++;
    expected.a <<= 1;
    expected.a |= 1; // the carry flag is now in bit 0
    expected.p.c = false;
    run<ROLInstruction>(AddressingMode::ACC, 2, expected);

    registers.reset();
    registers.a = 0x80;
    expected = registers;
    expected.pc++;
    expected.a = 0;
    expected.p.z = true;
    expected.p.c = true;
    run<ROLInstruction>(AddressingMode::ACC, 2, expected);

    registers.reset();
    registers.a = 0x40;
    expected = registers;
    expected.pc++;
    expected.p.n = true;
    expected.a <<= 1;
    run<ROLInstruction>(AddressingMode::ACC, 2, expected);
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
    auto expected = registers;
    expected.p.c = true;
    expected.pc++;
    run<SECInstruction>(AddressingMode::IMP, 2, expected);

    expected.p.c = true;
    expected.pc++;
    run<SECInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, RTITest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, EORTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, LSRAccumulatorTest)
{
    registers.a = 0x08;
    auto expected = registers;
    expected.pc++;
    expected.a >>= 1;
    run<LSRInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 0x09;
    expected = registers;
    expected.pc++;
    expected.a >>=1;
    expected.p.c = true;
    run<LSRInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 0x00;
    expected = registers;
    expected.pc++;
    expected.p.c = false;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ACC, 2, expected);

    registers.a = 0x01;
    expected = registers;
    expected.pc++;
    expected.a >>=1;
    expected.p.c = true;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ACC, 2, expected);

    // we don't have to test the negative flag. shifting to the right will never result in
    // a negative flag. if it actually does (it shouldn't) then one of the above tests will fail for us.
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
    auto expected = registers;
    registers.p.i = true;
    expected.p.i = false;
    expected.pc++;
    run<CLIInstruction>(AddressingMode::IMP, 2, expected);
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
    registers.a = 0x80;
    auto expected = registers;
    expected.pc++;
    expected.a >>= 1;
    run<RORInstruction>(AddressingMode::ACC, 2, expected);

    registers.a |= 0x01;
    expected = registers;
    expected.pc++;
    expected.a >>= 1;
    expected.p.c = true;
    run<RORInstruction>(AddressingMode::ACC, 2, expected);

    expected.pc++;
    expected.a >>= 1;
    expected.a |= 0x80;
    expected.p.c = false;
    expected.p.n = true;
    expected.p.z = false;
    run<RORInstruction>(AddressingMode::ACC, 2, expected);

    registers.reset();
    registers.a = 1;
    expected = registers;
    expected.pc++;
    expected.a = 0;
    expected.p.c = true;
    expected.p.n = false;
    expected.p.z = true;
    run<RORInstruction>(AddressingMode::ACC, 2, expected);
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
    auto expected = registers;
    registers.p.i = false;
    expected.p.i = true;
    expected.pc++;
    run<SEIInstruction>(AddressingMode::IMP, 2, expected);
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
    registers.y = 15;

    auto expected = registers;
    expected.y--;
    expected.pc++;
    run<DEYInstruction>(AddressingMode::IMP, 2, expected);

    registers.y  = 1;
    expected.y   = 0;
    expected.p.z = true;
    expected.p.n = false;
    expected.pc++;
    run<DEYInstruction>(AddressingMode::IMP, 2, expected);


    expected.p.z = false;
    expected.p.n = true;
    expected.y = 255;
    expected.pc++;
    run<DEYInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, TXATest)
{
    registers.x = 15;
    auto expected = registers;
    expected.a = registers.x;
    expected.pc++;
    run<TXAInstruction>(AddressingMode::IMP, 2, expected);

    registers.x = 0;
    expected = registers;
    expected.pc++;
    expected.a = registers.x;
    expected.p.z = true;
    run<TXAInstruction>(AddressingMode::IMP, 2, expected);

    registers.x = 128;
    expected = registers;
    expected.pc++;
    expected.a = registers.x;
    expected.p.z = false;
    expected.p.n = true;
    run<TXAInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, BCCTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, TYATest)
{
    registers.y = 15;
    auto expected = registers;
    expected.a = registers.y;
    expected.pc++;
    run<TYAInstruction>(AddressingMode::IMP, 2, expected);

    registers.y = 0;
    expected = registers;
    expected.pc++;
    expected.a = registers.y;
    expected.p.z = true;
    run<TYAInstruction>(AddressingMode::IMP, 2, expected);

    registers.y = 128;
    expected = registers;
    expected.pc++;
    expected.a = registers.y;
    expected.p.z = false;
    expected.p.n = true;
    run<TYAInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, TXSTest)
{
    registers.x = 15;
    auto expected = registers;
    expected.pc++;
    expected.sp = registers.x;
    run<TXSInstruction>(AddressingMode::IMP, 2, expected);
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
    registers.a = 15;

    auto expected = registers;
    expected.pc++;
    expected.y = expected.a;
    run<TAYInstruction>(AddressingMode::IMP, 2, expected);

    registers.a = 255;
    expected = registers;

    expected.pc++;
    expected.a = 255;
    expected.y = 255;
    expected.p.n = true;
    run<TAYInstruction>(AddressingMode::IMP, 2, expected);


    registers.a = 0;
    
    expected = registers;
    expected.pc++;
    expected.y = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<TAYInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, TAXTest)
{
    registers.a = 15;

    auto expected = registers;
    expected.pc++;
    expected.x = expected.a;
    run<TAXInstruction>(AddressingMode::IMP, 2, expected);

    registers.a = 255;
    expected = registers;

    expected.pc++;
    expected.a = 255;
    expected.x = 255;
    expected.p.n = true;
    run<TAXInstruction>(AddressingMode::IMP, 2, expected);


    registers.a = 0;
    
    expected = registers;
    expected.pc++;
    expected.x = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<TAXInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, BCSTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, CLVTest)
{
    auto expected = registers;
    registers.p.v = true;
    expected.p.v = false;
    expected.pc++;
    run<CLVInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, TSXTest)
{
    registers.sp = 15;
    auto expected = registers;
    expected.pc++;
    expected.x = registers.sp;
    run<TSXInstruction>(AddressingMode::IMP, 2, expected);

    registers.sp = 0;
    expected = registers;
    expected.pc++;
    expected.x = registers.sp;
    expected.p.z = true;
    run<TSXInstruction>(AddressingMode::IMP, 2, expected);

    registers.sp = 128;
    expected = registers;
    expected.pc++;
    expected.x = registers.sp;
    expected.p.n = true;
    expected.p.z = false;
    run<TSXInstruction>(AddressingMode::IMP, 2, expected);
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
    registers.y = 15;

    // test normal behaviour. x should be incremented
    auto expected = registers;
    expected.y++;
    expected.pc++;
    run<INYInstruction>(AddressingMode::IMP, 2, expected);

    // negative flag should be set if bit 7 is high
    registers.y = 127;
    expected.y = 128;
    expected.p.n = true;
    expected.pc++;
    run<INYInstruction>(AddressingMode::IMP, 2, expected);

    // zero flag should be set if the entire value of x is zero
    registers.y = 255;
    expected.y = 0;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc++;
    run<INYInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, DEXTest)
{
    registers.x = 15;

    auto expected = registers;
    expected.x--;
    expected.pc++;
    run<DEXInstruction>(AddressingMode::IMP, 2, expected);

    registers.x  = 1;
    expected.x   = 0;
    expected.p.z = true;
    expected.p.n = false;
    expected.pc++;
    run<DEXInstruction>(AddressingMode::IMP, 2, expected);


    expected.p.z = false;
    expected.p.n = true;
    expected.x = 255;
    expected.pc++;
    run<DEXInstruction>(AddressingMode::IMP, 2, expected);
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
    registers.x = 15;

    // test normal behaviour. x should be incremented
    auto expected = registers;
    expected.x++;
    expected.pc++;
    run<INXInstruction>(AddressingMode::IMP, 2, expected);

    // negative flag should be set if bit 7 is high
    registers.x = 127;
    expected.x = 128;
    expected.p.n = true;
    expected.pc++;
    run<INXInstruction>(AddressingMode::IMP, 2, expected);

    // zero flag should be set if the entire value of x is zero
    registers.x = 255;
    expected.x = 0;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc++;
    run<INXInstruction>(AddressingMode::IMP, 2, expected);
}

TEST_F(InstructionTestFixture, BEQTest)
{
    FAIL() << "Not yet implemented";
}

TEST_F(InstructionTestFixture, SEDTest)
{
    auto expected = registers;
    expected.p.d = true;
    expected.pc++;
    run<SEDInstruction>(AddressingMode::IMP, 2, expected);

    expected.p.d = true;
    expected.pc++;
    run<SEDInstruction>(AddressingMode::IMP, 2, expected);
}