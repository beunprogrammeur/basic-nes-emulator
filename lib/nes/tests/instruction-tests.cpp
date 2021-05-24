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
    MockBus()                                                          { for(int i = 0; i < size; i++) _memory[i] = 0x77; } // never test againts 0x77. if that number is found the instruction is broken
    virtual uint8_t read(uint16_t address) const                       { return _memory[address];  }                        // or specific bus address is not inintialized properly
    virtual void    write(uint16_t address, uint8_t value)             { _memory[address] = value; }
    virtual void    connect(nes::peripherals::IPeripheral& peripheral) { /* not used */            }
};

// used for the LD[A,X,Y] and ST[A,X,Y] instructions
enum class reg {
    a,x,y
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
        EXPECT_EQ(expected.p.n, registers.p.n) << "expected negative flag to be "   << expected.p.n << " but it was " << registers.p.n;
        EXPECT_EQ(expected.p.u, registers.p.u) << "expected unused flag to be "     << expected.p.u << " but it was " << registers.p.u;
        EXPECT_EQ(expected.p.v, registers.p.v) << "expected overflow flag to be "   << expected.p.v << " but it was " << registers.p.v;
        EXPECT_EQ(expected.p.b, registers.p.b) << "expected break flag to be "      << expected.p.b << " but it was " << registers.p.b;
        EXPECT_EQ(expected.p.d, registers.p.d) << "expected decimal flag to be "    << expected.p.d << " but it was " << registers.p.d;
        EXPECT_EQ(expected.p.i, registers.p.i) << "expected IRQ flag to be "        << expected.p.i << " but it was " << registers.p.i;
        EXPECT_EQ(expected.p.z, registers.p.z) << "expected zero flag to be "       << expected.p.z << " but it was " << registers.p.z;
        EXPECT_EQ(expected.p.c, registers.p.c) << "expected carry flag to be "      << expected.p.c << " but it was " << registers.p.c;
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
    void load(uint16_t startAddress, std::initializer_list<uint8_t> binary)
    {
        int i = 1;
        for(auto byte : binary)
        {
            bus->write(startAddress + i++, byte);
        }

        registers.pc = startAddress;
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

    // push value onto the stack
    void push(uint8_t value)
    {
        bus->write(0x0100 | registers.sp--, value);
    }

    void LDNImmediateTest(BaseInstruction& instruction, reg instructionReg)
    {
        instruction.setMode(AddressingMode::IMM);

        auto expected = registers;
        uint8_t* cmpreg = &expected.a;

        switch(instructionReg)
        {
            case reg::x: cmpreg = &expected.x; break;
            case reg::y: cmpreg = &expected.y; break;
        }


        load(0xFF00, {0x80});
        *cmpreg      = 0x80;
        expected.pc  = registers.pc + 2;
        expected.p.n = true;

        execute(instruction, 2, false);
        compare(expected);

        load(0xFF00, {0x00});
        *cmpreg      = 0x00;
        expected.pc = registers.pc + 2;
        expected.p.n = false;
        expected.p.z = true;

        execute(instruction, 2, false);
        compare(expected);
    }

    void LDNZeroPageTest(BaseInstruction& instruction, reg instructionReg)
    {
        instruction.setMode(AddressingMode::ZP);

        auto expected = registers;
        uint8_t* cmpreg = &expected.a;

        switch(instructionReg)
        {
            case reg::x: cmpreg = &expected.x; break;
            case reg::y: cmpreg = &expected.y; break;
        }


        load(0xFF00, {0x40});
        bus->write(0x40, 0x80);
        *cmpreg      = 0x80;
        expected.pc  = registers.pc + 2;
        expected.p.n = true;

        execute(instruction, 3, false);
        compare(expected);

        load(0xFF00, {0x40});
        bus->write(0x40, 0x00);
        *cmpreg      = 0x00;
        expected.pc = registers.pc + 2;
        expected.p.n = false;
        expected.p.z = true;

        execute(instruction, 3, false);
        compare(expected);
    }

    void LDNZeroPageXYTest(BaseInstruction& instruction, reg instructionReg, reg addReg)
    {
        auto expected = registers;

        auto mode       = AddressingMode::ZPX;
        uint8_t* cmpreg = &expected.a;

        registers.x = -3;
        expected.x  = -3;

        switch(instructionReg)
        {
            case reg::x: 
                cmpreg = &expected.x; 
                mode = AddressingMode::ZPY;
                registers.y = -3;
                expected.y  = -3;
                break;
            case reg::y: 
                cmpreg = &expected.y; 
                mode = AddressingMode::ZPX;
                registers.x = -3;
                expected.x  = -3;
                break;
        }

        instruction.setMode(mode);

        // also does a page boundary 
        load(0xFF00, {0x02});
        bus->write(0xFF, 0x80); // zeropage xy wraps around in page 0
        *cmpreg      = 0x80;
        expected.pc  = registers.pc + 2;
        expected.p.n = true;
        
        execute(instruction, 4, false);
        compare(expected);

        load(0xFF00, {0x02});
        bus->write(0xFF, 0x00);
        *cmpreg      = 0x00;
        expected.pc = registers.pc + 2;
        expected.p.n = false;
        expected.p.z = true;

        execute(instruction, 4, false);
        compare(expected);
    }

    void LDNAbsoluteTest(BaseInstruction& instruction, reg instructionReg)
    {
        instruction.setMode(AddressingMode::ABS);

        auto expected = registers;
        uint8_t* cmpreg = &expected.a;

        switch(instructionReg)
        {
            case reg::x: cmpreg = &expected.x; break;
            case reg::y: cmpreg = &expected.y; break;
        }


        load(0xFF00, {0x20, 0x04});
        bus->write(0x420, 0x80);
        *cmpreg      = 0x80;
        expected.pc  = registers.pc + 2;
        expected.p.n = true;

        execute(instruction, 4, false);
        compare(expected);

        load(0xFF00, {0x20, 0x04});
        bus->write(0x420, 0x00);
        *cmpreg      = 0x00;
        expected.pc = registers.pc + 2;
        expected.p.n = false;
        expected.p.z = true;

        execute(instruction, 4, false);
        compare(expected);
    }

    void LDNAbsoluteXYTest(BaseInstruction& instruction, reg instructionReg, reg addReg)
    {
        auto expected = registers;

        auto mode       = AddressingMode::ABSX;
        uint8_t* cmpreg = &expected.a;

        registers.x = -1;
        expected.x  = -1;

        switch(instructionReg)
        {
            case reg::x: 
                cmpreg = &expected.x; 
                mode = AddressingMode::ABSY;
                registers.y = -1;
                expected.y  = -1;
                break;
            case reg::y: 
                cmpreg = &expected.y; 
                mode = AddressingMode::ABSX;
                registers.x = -1;
                expected.x  = -1;
                break;
        }

        instruction.setMode(mode);



        // also does a page boundary 
        load(0xFF00, {0x00, 0x04});
        bus->write(0x3FF, 0x80);
        *cmpreg      = 0x80;
        expected.pc  = registers.pc + 3;
        expected.p.n = true;
        
        execute(instruction, 5, false);
        compare(expected);

        load(0xFF00, {0x21, 0x04});
        bus->write(0x420, 0x00);
        *cmpreg      = 0x00;
        expected.pc = registers.pc + 3;
        expected.p.n = false;
        expected.p.z = true;

        execute(instruction, 4, false);
        compare(expected);
    }

    void STNZPTest(BaseInstruction& instruction, uint8_t& source)
    {
        instruction.setMode(AddressingMode::ZP);


        load(0xFF00, {0x14});
        source = 0xB0; // value to write to the above address
        auto expected = registers;
        expected.pc += 2;

        execute(instruction, 3, false);
        compare(expected);
        EXPECT_EQ(0xB0, bus->read(0x14));
    }

    void STNABSTest(BaseInstruction& instruction, uint8_t& source)
    {
        instruction.setMode(AddressingMode::ABS);

        load(0xFF00, {0xBA, 0xAB});
        source = 0xB0; // value to write to the above address
        auto expected = registers;
        expected.pc += 3;

        execute(instruction, 4, false);
        compare(expected);
        EXPECT_EQ(0xB0, bus->read(0xABBA));
    }

    void STNZPXYTest(BaseInstruction& instruction, uint8_t& source, reg addReg)
    {
        switch(addReg)
        {
            case reg::x:
                instruction.setMode(AddressingMode::ZPX);
                registers.x = -1;
                break;
            case reg::y:
                instruction.setMode(AddressingMode::ZPY);
                registers.y = -1;
                break;
        }

        load(0xFF00, {0x02});
        source = 0xB0;
        auto expected = registers;
        expected.pc += 2;
        execute(instruction, 4, false);
        compare(expected);
        EXPECT_EQ(0xB0, bus->read(0x01));
    }

    void STNABSXYTest(BaseInstruction& instruction, uint8_t& source, reg addReg)
    {
        switch(addReg)
        {
            case reg::x:
                instruction.setMode(AddressingMode::ABSX);
                registers.x = -1;
                break;
            case reg::y:
                instruction.setMode(AddressingMode::ABSY);
                registers.y = -1;
                break;
        }

        load(0xFF00, {0xBB, 0xAB});
        source = 0xB0;
        auto expected = registers;
        expected.pc += 3;
        execute(instruction, 5, false);
        compare(expected);
        EXPECT_EQ(0xB0, bus->read(0xABBA));
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
        lo(expected.pc),
        hi(expected.pc),
    });
}

TEST_F(InstructionTestFixture, ORAImmediateTest)
{
    load(0xFF00, {0xf0});
    registers.a = 0x01;
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0xf1;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::IMM, 2, expected);

    load(0xFF00, {0x00});
    registers.a = 0x00;
    expected = registers;
    expected.pc += 2;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, ORAZeroPageTest)
{
    load(0xFF00, {0xf0});
    bus->write(0xf0, 0x80);
    registers.a = 0x01;
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x81;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::ZP, 3, expected);

    load(0xFF00, {0xaa});
    bus->write(0xaa, 0x00);
    registers.a = 0x00;
    expected = registers;
    expected.pc += 2;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::ZP, 3, expected);
}

TEST_F(InstructionTestFixture, ORAZeroPageXTest)
{
    load(0xFF00, {0xf0});
    bus->write(0xf1, 0x80);
    registers.a = 0x01;
    registers.x = 0x01; // added to the address
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x81;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::ZPX, 4, expected);

    load(0xFF00, {0xff});
    bus->write(0x01, 0x44);
    registers.x = 0x02;
    registers.a = 0x11;
    expected = registers;
    expected.pc += 2;
    expected.a = 0x55;
    expected.p.n = false;
    expected.p.z = false;
    run<ORAInstruction>(AddressingMode::ZPX, 4, expected);

    load(0xFF00, {0xff});
    bus->write(0x02, 0x0);
    registers.x = 0x03;
    registers.a = 0x00;
    expected = registers;
    expected.pc += 2;
    expected.a = 0x00;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::ZPX, 4, expected);
}

TEST_F(InstructionTestFixture, ORAAbsoluteTest)
{
    load(0xFF00, {0xef, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::ABS, 4, expected);

    load(0xFF00, {0x0d, 0xd0});
    bus->write(0xd00d, 0x00);
    bus->write(0x0dd0, 0xff); // to make sure this fails if the msb and lsd are swapped
    registers.a = 0x00;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::ABS, 4, expected);
}

TEST_F(InstructionTestFixture, ORAAbsoluteXTest)
{
    load(0xFF00, {0xee, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    registers.x = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::ABSX, 4, expected);

    load(0xFF00, {0x0e, 0xd0});
    bus->write(0xd00d, 0x00);
    bus->write(0x0dd0, 0xff); // to make sure this fails if the msb and lsd are swapped
    registers.a = 0x00;
    registers.x = -1;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::ABSX, 4, expected);

    // cross page
    load(0xFF00, {0x00, 0xAA}); // addr 0xAA00, -1 is 0xA9FF thus page boundary crossed
    bus->write(0xA9FF, 0x11);
    registers.a = 0x44;
    registers.x = -1; // addr - 1 = 0xa9ff
    expected = registers;
    expected.pc += 3;
    expected.a = 0x55;
    expected.p.z = false;
    run<ORAInstruction>(AddressingMode::ABSX, 5, expected); // page cross + 1 tick
}

TEST_F(InstructionTestFixture, ORAAbsoluteYTest)
{
    load(0xFF00, {0xee, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    registers.y = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::ABSY, 4, expected);

    load(0xFF00, {0x0e, 0xd0});
    bus->write(0xd00d, 0x00);
    bus->write(0x0dd0, 0xff); // to make sure this fails if the msb and lsd are swapped
    registers.a = 0x00;
    registers.y = -1;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::ABSY, 4, expected);

    // cross page
    load(0xFF00, {0x00, 0xAA}); // addr 0xAA00, -1 is 0xA9FF thus page boundary crossed
    bus->write(0xA9FF, 0x11);
    registers.a = 0x44;
    registers.y = -1; // addr - 1 = 0xa9ff
    expected = registers;
    expected.pc += 3;
    expected.a = 0x55;
    expected.p.z = false;
    run<ORAInstruction>(AddressingMode::ABSY, 5, expected); // page cross + 1 tick
}

TEST_F(InstructionTestFixture, ORAIndirectXTest)
{
    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x50;
    bus->write(0x02, 0x05);

    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x55;
    run<ORAInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x00;
    bus->write(0x02, 0x00);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x00;
    expected.p.z = true;
    run<ORAInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x01;
    bus->write(0x02, 0x80);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x81;
    expected.p.z = false;
    expected.p.n = true;
    run<ORAInstruction>(AddressingMode::IINDX, 6, expected);
}

TEST_F(InstructionTestFixture, ORAIndirectYTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0x06, 0x80);
    registers.a = 0x01;
    registers.y = 0x01;

    auto expected = registers;
    expected.pc += 2;
    expected.p.n = true;
    expected.a = 0x81;
    run<ORAInstruction>(AddressingMode::IINDY, 5, expected);

    // page cross test
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0xFFFF, 0x00); // wraparound
    registers.a = 0x00;
    registers.y = -6;

    expected = registers;
    expected.pc += 2;
    expected.p.z = true;
    expected.p.n = false;
    expected.a = 0x00;
    run<ORAInstruction>(AddressingMode::IINDY, 6, expected);
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

TEST_F(InstructionTestFixture, ASLZeroPageTest)
{
    load(0xFF00, {0xBA});
    bus->write(0xBA, 0x80);
    auto expected = registers;
    expected.pc += 3;
    expected.p.z = true;
    expected.p.c = true;
    run<ASLInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x00, bus->read(0xBA));

    load(0xFF00, {0xBA});
    bus->write(0xBA, 0x40);
    expected = registers;
    expected.pc += 3;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    run<ASLInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x80, bus->read(0xBA));
}

TEST_F(InstructionTestFixture, ASLZeroPageXTest)
{
    load(0xFF00, {0xBA});
    bus->write(0xBA, 0x80);
    auto expected = registers;
    expected.pc += 2;
    expected.p.z = true;
    expected.p.c = true;
    run<ASLInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x00, bus->read(0xBA));

    load(0xFF00, {0xBA});
    bus->write(0xBA, 0x40);
    expected = registers;
    expected.pc += 2;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    run<ASLInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x80, bus->read(0xBA));
}

TEST_F(InstructionTestFixture, ASLAbsoluteTest)
{
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x80);
    auto expected = registers;
    expected.pc += 3;
    expected.p.z = true;
    expected.p.c = true;
    run<ASLInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x00, bus->read(0xABBA));

    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x40);
    expected = registers;
    expected.pc += 3;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    run<ASLInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x80, bus->read(0xABBA));
}

TEST_F(InstructionTestFixture, ASLAbsoluteXTest)
{
    load(0xFF00, {0xB9, 0xAB});
    bus->write(0xABBA, 0x80);
    registers.x = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.p.z = true;
    expected.p.c = true;
    run<ASLInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x00, bus->read(0xABBA));

    load(0xFF00, {0xB9, 0xAB});
    bus->write(0xABBA, 0x40);
    registers.x = 0x01;
    expected = registers;
    expected.pc += 3;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    run<ASLInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x80, bus->read(0xABBA));
}

TEST_F(InstructionTestFixture, PHPTest)
{
    registers.p.n = true;
    registers.p.z = true;
    registers.p.d = true;
    auto expected = registers;
    expected.pc++;
    expected.sp--;

    run<PHPInstruction>(AddressingMode::IMP, 3, expected);
    stackcmp({registers.p.toByte()});
}

TEST_F(InstructionTestFixture, BPLTest)
{
    load(0xFF00, {0x00}); // load a 0, we don't really need to do anything because the negative flag is true
    registers.p.n = true;
    auto expected = registers;
    expected.pc += 2;
    run<BPLInstruction>(AddressingMode::REL, 2, expected);

    load(0xFF00, {0x04});
    registers.p.n = false;
    expected = registers;
    expected.pc = 0xFF04;
    run<BPLInstruction>(AddressingMode::REL, 3, expected);
    

    load(0xFF00, {static_cast<uint8_t>(-1)}); // jump -1 so we hop to the previous page
    registers.p.n = false;
    expected = registers;
    expected.pc = 0xFF00 -1;
    run<BPLInstruction>(AddressingMode::REL, 4, expected);
    

}

TEST_F(InstructionTestFixture, JSRTest)
{
    load(0xFF00, {0xBA, 0xAB});
    auto expected = registers;
    expected.pc  = 0xABBA;
    expected.sp -= 2;
    run<JSRInstruction>(AddressingMode::ABS, 6, expected);
    stackcmp({0x02, 0xFF});
}

TEST_F(InstructionTestFixture, ANDImmediateTest)
{
    load(0xFF00, {0x80});
    registers.a = 0x81;
    auto expected = registers;
    expected.pc +=2;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::IMM, 2, expected);

    load(0xFF00, {0x80});
    registers.a = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=2;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, ANDZeroPageTest)
{
    load(0xFF00, {0x40});
    bus->write(0x40, 0x80);
    registers.a = 0x81;
    auto expected = registers;
    expected.pc +=2;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::ZP, 3, expected);

    load(0xFF00, {0x40});
    bus->write(0x40, 0x80);
    registers.a = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=2;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ZP, 3, expected);
}

TEST_F(InstructionTestFixture, ANDZeroPageXTest)
{
    load(0xFF00, {0x3f});
    bus->write(0x40, 0x80);
    registers.a = 0x81;
    registers.x = 0x01;
    auto expected = registers;
    expected.pc +=2;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::ZPX, 4, expected);

    load(0xFF00, {0x3f});
    bus->write(0x40, 0x80);
    registers.a = 0x01;
    registers.x = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=2;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ZPX, 4, expected);
}

TEST_F(InstructionTestFixture, ANDAbsoluteTest)
{
    load(0xFF00, {0x40, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x81;
    auto expected = registers;
    expected.pc +=3;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::ABS, 4, expected);

    load(0xFF00, {0x40, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=3;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ABS, 4, expected);
}

TEST_F(InstructionTestFixture, ANDAbsoluteXTest)
{
    load(0xFF00, {0x3f, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x81;
    registers.x = 0x01;
    auto expected = registers;
    expected.pc +=3;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::ABSX, 4, expected);

    load(0xFF00, {0x3f, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x01;
    registers.x = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=3;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ABSX, 4, expected);


    load(0xFF00, {0xFF, 0x02});
    bus->write(0x0300, 0x80);
    registers.a = 0x01;
    registers.x = 0x1;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=3;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ABSX, 5, expected);
}

TEST_F(InstructionTestFixture, ANDAbsoluteYTest)
{
    load(0xFF00, {0x3f, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x81;
    registers.y = 0x01;
    auto expected = registers;
    expected.pc +=3;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::ABSY, 4, expected);

    load(0xFF00, {0x3f, 0x02});
    bus->write(0x0240, 0x80);
    registers.a = 0x01;
    registers.y = 0x01;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=3;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ABSY, 4, expected);


    load(0xFF00, {0xFF, 0x02});
    bus->write(0x0300, 0x80);
    registers.a = 0x01;
    registers.y = 0x1;
    expected = registers;
    expected.a = 0x00;
    expected.pc +=3;
    expected.p.n = false;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::ABSY, 5, expected);
}

TEST_F(InstructionTestFixture, ANDIndirectXTest)
{
    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0xf5;
    bus->write(0x02, 0x05);

    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x05;
    run<ANDInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0xf5;
    bus->write(0x02, 0x00);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x00;
    expected.p.z = true;
    run<ANDInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0xef;
    bus->write(0x02, 0x80);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x80;
    expected.p.z = false;
    expected.p.n = true;
    run<ANDInstruction>(AddressingMode::IINDX, 6, expected);
}

TEST_F(InstructionTestFixture, ANDIndirectYTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0x06, 0x80);
    registers.a = 0x81;
    registers.y = 0x01;

    auto expected = registers;
    expected.pc += 2;
    expected.p.n = true;
    expected.a = 0x80;
    run<ANDInstruction>(AddressingMode::IINDY, 5, expected);

    // page cross test
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0xFFFF, 0x00); // wraparound
    registers.a = 0x00;
    registers.y = -6;

    expected = registers;
    expected.pc += 2;
    expected.p.z = true;
    expected.p.n = false;
    expected.a = 0x00;
    run<ANDInstruction>(AddressingMode::IINDY, 6, expected);
}

TEST_F(InstructionTestFixture, BITZeroPageTest)
{
    bus->write(0xABBA, 0x55);
    load(0xFF00, {0xBA, 0xAB});
    registers.a = 0x00;
    auto expected = registers;
    expected.pc += 3;
    expected.p.z = true;
    run<BITInstruction>(AddressingMode::ABS, 4, expected);

    bus->write(0xAB, 0x81);
    load(0xFF00, {0xAB});
    registers.a = 0xf0;
    expected = registers;
    expected.pc += 3;
    expected.p.z = false;
    expected.p.n = true;
    run<BITInstruction>(AddressingMode::ABS, 4, expected);
}

TEST_F(InstructionTestFixture, BITAbsoluteTest)
{
    bus->write(0xABBA, 0x55);
    load(0xFF00, {0xBA, 0xAB});
    registers.a = 0x00;
    auto expected = registers;
    expected.pc += 3;
    expected.p.z = true;
    run<BITInstruction>(AddressingMode::ABS, 4, expected);

    bus->write(0xABBA, 0x81);
    load(0xFF00, {0xBA, 0xAB});
    registers.a = 0xf0;
    expected = registers;
    expected.pc += 3;
    expected.p.z = false;
    expected.p.n = true;
    run<BITInstruction>(AddressingMode::ABS, 4, expected);
}


TEST_F(InstructionTestFixture, RORAccummulatorTest)
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

    registers.a = 0x00;
    registers.p.c = true;
    expected = registers;
    expected.pc++;
    expected.a = 0x80;
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

TEST_F(InstructionTestFixture, RORZeroPageTest)
{
    load(0xFF00, {0x04});
    bus->write(0x04, 0x00);
    auto expected = registers;
    registers.p.c = true;
    expected.pc += 2;
    expected.p.n = true;
    run<RORInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x80, bus->read(0x04));

    load(0xFF00, {0x04});
    bus->write(0x04, 0x01);
    expected = registers;
    expected.pc += 2;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<RORInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x00, bus->read(0x04));
}

TEST_F(InstructionTestFixture, RORZeroPageXTest)
{
    load(0xFF00, {0x03});
    bus->write(0x04, 0x00);
    registers.x = 0x01;
    auto expected = registers;
    registers.p.c = true;
    expected.pc += 2;
    expected.p.n = true;
    run<RORInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x04));

    load(0xFF00, {0x03});
    bus->write(0x04, 0x01);
    registers.x = 0x01;
    expected = registers;
    expected.pc += 2;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<RORInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x04));
}

TEST_F(InstructionTestFixture, RORAbsoluteTest)
{
    load(0xFF00, {0x04, 0x04});
    bus->write(0x0404, 0x00);
    auto expected = registers;
    registers.p.c = true;
    expected.pc += 3;
    expected.p.n = true;
    run<RORInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x0404));

    load(0xFF00, {0x04, 0x04});
    bus->write(0x0404, 0x01);
    expected = registers;
    expected.pc += 3;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<RORInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x0404));
}

TEST_F(InstructionTestFixture, RORAbsoluteXTest)
{
    load(0xFF00, {0x03, 0x04});
    bus->write(0x0404, 0x00);
    registers.x = 0x01;
    auto expected = registers;
    registers.p.c = true;
    expected.pc += 3;
    expected.p.n = true;
    run<RORInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x80, bus->read(0x0404));

    load(0xFF00, {0x03, 0x04});
    bus->write(0x0404, 0x01);
    registers.x = 0x01;
    expected = registers;
    expected.pc += 3;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<RORInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x00, bus->read(0x0404));
}

TEST_F(InstructionTestFixture, ROLAccumulatorTest)
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

TEST_F(InstructionTestFixture, ROLZeroPageTest)
{
    load(0xFF00, {0x04});
    bus->write(0x04, 0x40);
    auto expected = registers;
    expected.pc += 2;
    expected.p.n = true;
    run<ROLInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x80, bus->read(0x04));

    load(0xFF00, {0x04});
    bus->write(0x04, 0x80);
    expected = registers;
    expected.pc += 2;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<ROLInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x00, bus->read(0x04));
}

TEST_F(InstructionTestFixture, ROLZeroPageXTest)
{
    load(0xFF00, {0x03});
    bus->write(0x04, 0x40);
    registers.x = 0x01;
    auto expected = registers;
    expected.pc += 2;
    expected.p.n = true;
    run<ROLInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x04));

    load(0xFF00, {0x03});
    bus->write(0x04, 0x80);
    registers.x = 0x01;
    expected = registers;
    expected.pc += 2;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<ROLInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x04));
}

TEST_F(InstructionTestFixture, ROLAbsoluteTest)
{
    load(0xFF00, {0x04, 0x04});
    bus->write(0x0404, 0x40);
    auto expected = registers;
    expected.pc += 3;
    expected.p.n = true;
    run<ROLInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x0404));

    load(0xFF00, {0x04, 0x04});
    bus->write(0x0404, 0x80);
    expected = registers;
    expected.pc += 3;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<ROLInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x0404));
}

TEST_F(InstructionTestFixture, ROLAbsoluteXTest)
{
    load(0xFF00, {0x03, 0x04});
    bus->write(0x0404, 0x40);
    registers.x = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.p.n = true;
    run<ROLInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x80, bus->read(0x0404));

    load(0xFF00, {0x03, 0x04});
    bus->write(0x0404, 0x80);
    registers.x = 0x01;
    expected = registers;
    expected.pc += 3;
    expected.p.n = false;
    expected.p.c = true;
    expected.p.z = true;
    run<ROLInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x00, bus->read(0x0404));
}

TEST_F(InstructionTestFixture, PLPTest)
{
    auto expected = registers;
    expected.p.n = true;
    expected.p.c = true;
    expected.p.d = true;
    expected.pc++;
    push(expected.p.toByte()); // we push, the opcode pulls, so the sp is as it was
    run<PLPInstruction>(AddressingMode::IMP, 4, expected);
}

TEST_F(InstructionTestFixture, BMITest)
{
    load(0xFF00, {0x00}); // load a 0, we don't really need to do anything because the negative flag is false
    registers.p.n = false;
    auto expected = registers;
    expected.pc += 2;
    run<BMIInstruction>(AddressingMode::REL, 2, expected);

    load(0xFF00, {0x04});
    registers.p.n = true;
    expected = registers;
    expected.pc = 0xFF04;
    run<BMIInstruction>(AddressingMode::REL, 3, expected);
    

    load(0xFF00, {static_cast<uint8_t>(-1)}); // jump -1 so we hop to the previous page
    registers.p.n = true;
    expected = registers;
    expected.pc = 0xFF00 -1;
    run<BMIInstruction>(AddressingMode::REL, 4, expected);
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
    auto expected = registers;

    // set some recognizable flags
    expected.p.c = true;
    expected.p.v = true;
    expected.p.n = true;
    expected.pc = 0xABBA;
    push(hi(expected.pc));
    push(lo(expected.pc));
    push(expected.p.toByte());
    run<RTIInstruction>(AddressingMode::IMP, 6, expected);
}

TEST_F(InstructionTestFixture, EORImmediateTest)
{
    load(0xFF00, {0xff});
    registers.a = 0x7f;
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x80;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::IMM, 2, expected);

    load(0xFF00, {0xff});
    registers.a = 0xff;
    expected = registers;
    expected.pc += 2;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, EORZeroPageTest)
{
    load(0xFF00, {0xf0});
    bus->write(0xf0, 0xff);
    registers.a = 0x7f;
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x80;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::ZP, 3, expected);

    load(0xFF00, {0xaa});
    bus->write(0xaa, 0xff);
    registers.a = 0xff;
    expected = registers;
    expected.pc += 2;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::ZP, 3, expected);
}

TEST_F(InstructionTestFixture, EORZeroPageXTest)
{
    load(0xFF00, {0xf0});
    bus->write(0xf1, 0xfe);
    registers.a = 0x7f;
    registers.x = 0x01; // added to the address
    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x81;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::ZPX, 4, expected);

    load(0xFF00, {0xff});
    bus->write(0x01, 0xaa);
    registers.x = 0x02;
    registers.a = 0xff;
    expected = registers;
    expected.pc += 2;
    expected.a = 0x55;
    expected.p.n = false;
    expected.p.z = false;
    run<EORInstruction>(AddressingMode::ZPX, 4, expected);

    load(0xFF00, {0xff});
    bus->write(0x02, 0x0f);
    registers.x = 0x03;
    registers.a = 0x0f;
    expected = registers;
    expected.pc += 2;
    expected.a = 0x00;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::ZPX, 4, expected);
}

TEST_F(InstructionTestFixture, EORAbsoluteTest)
{
    load(0xFF00, {0xef, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::ABS, 4, expected);

    load(0xFF00, {0x0d, 0xd0});
    bus->write(0xd00d, 0x00);
    registers.a = 0x00;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::ABS, 4, expected);
}

TEST_F(InstructionTestFixture, EORAbsoluteXTest)
{
    load(0xFF00, {0xee, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    registers.x = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::ABSX, 4, expected);

    load(0xFF00, {0x0e, 0xd0});
    bus->write(0xd00d, 0x00);
    bus->write(0x0dd0, 0xff); // to make sure this fails if the msb and lsd are swapped
    registers.a = 0x00;
    registers.x = -1;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::ABSX, 4, expected);

    // cross page
    load(0xFF00, {0x00, 0xAA}); // addr 0xAA00, -1 is 0xA9FF thus page boundary crossed
    bus->write(0xA9FF, 0x11);
    registers.a = 0x44;
    registers.x = -1; // addr - 1 = 0xa9ff
    expected = registers;
    expected.pc += 3;
    expected.a = 0x55;
    expected.p.z = false;
    run<EORInstruction>(AddressingMode::ABSX, 5, expected); // page cross + 1 tick
}

TEST_F(InstructionTestFixture, EORAbsoluteYTest)
{
    load(0xFF00, {0xee, 0xbe});
    bus->write(0xbeef, 0x80);
    registers.a = 0x01;
    registers.y = 0x01;
    auto expected = registers;
    expected.pc += 3;
    expected.a = 0x81;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::ABSY, 4, expected);

    load(0xFF00, {0x0e, 0xd0});
    bus->write(0xd00d, 0x00);
    bus->write(0x0dd0, 0xff); // to make sure this fails if the msb and lsd are swapped
    registers.a = 0x00;
    registers.y = -1;
    expected = registers;
    expected.pc += 3;
    expected.a = 0;
    expected.p.n = false;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::ABSY, 4, expected);

    // cross page
    load(0xFF00, {0x00, 0xAA}); // addr 0xAA00, -1 is 0xA9FF thus page boundary crossed
    bus->write(0xA9FF, 0x11);
    registers.a = 0x44;
    registers.y = -1; // addr - 1 = 0xa9ff
    expected = registers;
    expected.pc += 3;
    expected.a = 0x55;
    expected.p.z = false;
    run<EORInstruction>(AddressingMode::ABSY, 5, expected); // page cross + 1 tick
}

TEST_F(InstructionTestFixture, EORIndirectXTest)
{
    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x50;
    bus->write(0x02, 0x05);

    auto expected = registers;
    expected.pc += 2;
    expected.a = 0x55;
    run<EORInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x00;
    bus->write(0x02, 0x00);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x00;
    expected.p.z = true;
    run<EORInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    registers.x = 0x01;
    registers.a = 0x01;
    bus->write(0x02, 0x80);

    expected = registers;
    expected.pc += 2;
    expected.a = 0x81;
    expected.p.z = false;
    expected.p.n = true;
    run<EORInstruction>(AddressingMode::IINDX, 6, expected);
}

TEST_F(InstructionTestFixture, EORIndirectYTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0x06, 0x80);
    registers.a = 0x01;
    registers.y = 0x01;

    auto expected = registers;
    expected.pc += 2;
    expected.p.n = true;
    expected.a = 0x81;
    run<EORInstruction>(AddressingMode::IINDY, 5, expected);

    // page cross test
    load(0xFF00, {0x01});
    bus->write(0x01, 0x05);
    bus->write(0xFFFF, 0x00); // wraparound
    registers.a = 0x00;
    registers.y = -6;

    expected = registers;
    expected.pc += 2;
    expected.p.z = true;
    expected.p.n = false;
    expected.a = 0x00;
    run<EORInstruction>(AddressingMode::IINDY, 6, expected);
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

TEST_F(InstructionTestFixture, LSRZPTest)
{
    load(0xFF00, {0xAB});
    bus->write(0xAB, 0x08);
    auto expected = registers;
    expected.pc+= 3;
    run<LSRInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(bus->read(0xAB), 0x08 >> 1);

    load(0xFF00, {0xAB});
    bus->write(0xAB, 0x09);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    run<LSRInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(bus->read(0xAB), 0x09 >> 1);

    load(0xFF00, {0xAB});
    bus->write(0xAB, 0x00);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = false;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(bus->read(0xAB), 0x00);

    load(0xFF00, {0xAB});
    bus->write(0xAB, 0x01);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(bus->read(0xAB), 0x00);
}

TEST_F(InstructionTestFixture, LSRAbsTest)
{
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x08);
    auto expected = registers;
    expected.pc+= 3;
    run<LSRInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x08 >> 1);

    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x09);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    run<LSRInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x09 >> 1);

    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x00);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = false;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x00);

    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x01);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x00);
}

TEST_F(InstructionTestFixture, LSRAbsXTest)
{
    registers.x = -1;
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 0x08);
    auto expected = registers;
    expected.pc+= 3;
    run<LSRInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x08 >> 1);

    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 0x09);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    run<LSRInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x09 >> 1);

    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 0x00);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = false;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x00);

    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 0x01);
    expected = registers;
    expected.pc+= 3;
    expected.p.c = true;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(bus->read(0xABBA), 0x00);
}

TEST_F(InstructionTestFixture, LSRZPXTest)
{
    registers.x = -1;
    load(0xFF00, {0xBB});
    bus->write(0xBA, 0x08);
    auto expected = registers;
    expected.pc+= 2;
    run<LSRInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(bus->read(0xBA), 0x08 >> 1);

    load(0xFF00, {0xBB});
    bus->write(0xBA, 0x09);
    expected = registers;
    expected.pc+= 2;
    expected.p.c = true;
    run<LSRInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(bus->read(0xBA), 0x09 >> 1);

    load(0xFF00, {0xBB});
    bus->write(0xBA, 0x00);
    expected = registers;
    expected.pc+= 2;
    expected.p.c = false;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(bus->read(0xBA), 0x00);

    load(0xFF00, {0xBB});
    bus->write(0xBA, 0x01);
    expected = registers;
    expected.pc+= 2;
    expected.p.c = true;
    expected.p.z = true;
    run<LSRInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(bus->read(0xBA), 0x00);
}

TEST_F(InstructionTestFixture, PHATest)
{
    registers.a = 37;
    auto expected = registers;
    expected.pc++;
    expected.sp--;
    run<PHAInstruction>(AddressingMode::IMP, 3, expected);
    stackcmp({37});
}

TEST_F(InstructionTestFixture, JMPIndirectTest)
{
    // from http://www.obelisk.me.uk/6502/reference.html#JMP
    // An original 6502 has does not correctly fetch the target address if the indirect vector falls on a page boundary (e.g. $xxFF where xx is any value from $00 to $FF).
    // In this case fetches the LSB from $xxFF as expected but takes the MSB from $xx00.
    // This is fixed in some later chips like the 65SC02 so for compatibility always ensure the indirect vector is not at the end of the page.

    auto expected = registers;
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 0x0D);
    bus->write(0xABBB, 0xD0);
    expected.pc = 0xD00D;
    run<JMPInstruction>(AddressingMode::IABS, 5, expected);


    // quirk on 6502: if the LSB of an indirect address e.g. pointer is on the upper boundary of a page
    // (basically, if the LSB is 255) then (normally) the MSB would be on address 0 from the first next page.
    // but instead it reads address 0 from the current page.
    bus->write(0xAAFF, 0xEF); // lsb;
    bus->write(0xAA00, 0xBE); // msb;

    load(0xFF00, {0xFF, 0xAA}); // write pointer 0xAAFF to address 0xFF01 (simulate 0xFF00 is the current instruction)
    expected.pc = 0xBEEF;
    run<JMPInstruction>(AddressingMode::IABS, 5, expected);
}

TEST_F(InstructionTestFixture, JMPAbsoluteTest)
{
    load(0xFF00, {0xBA, 0xAB}); // LSBFirst
    auto expected = registers;
    expected.pc = 0xABBA;
    run<JMPInstruction>(AddressingMode::ABS, 3, expected);
}

TEST_F(InstructionTestFixture, BVCTest)
{
    registers.p.v = true; // do not branch if true
    load(0xFF00, {10});
    auto expected = registers;
    expected.pc += 2;
    run<BVCInstruction>(AddressingMode::REL, 2, expected);

    registers.p.v = false;
    load(0xFF00, {10});
    expected = registers;
    expected.pc = registers.pc + 10;
    run<BVCInstruction>(AddressingMode::REL, 3, expected);

    load(0xFF00, {static_cast<uint8_t>(-1)});
    expected = registers;
    expected.pc = registers.pc -1;
    run<BVCInstruction>(AddressingMode::REL, 4, expected);
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
    auto expected = registers;
    expected.pc = 0xABBA -1;
    push(hi(0xABBA));
    push(lo(0xABBA));

    run<RTSInstruction>(AddressingMode::IMP, 6, expected);
}


TEST_F(InstructionTestFixture, ADCTest)
{
    // the implementation of all ADC opcodes is the same. reading method is standardized.
    // It's a lot of work, maybe we'll add those tests at some point
    load(0xFF00, {0x01});
    registers.a = -1;
    auto expected = registers;
    expected.a = 0;
    expected.pc += 2;
    expected.p.z = true;
    expected.p.c = true;
    run<ADCInstruction>(AddressingMode::IMM, 2, expected);

    load(0xFF00, {0xFF});
    registers.a = -127;
    expected = registers;
    expected.pc += 2;
    expected.p.z = false;
    expected.p.n = true;
    run<ADCInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, SBCTest)
{
    // same story as ADCTest
    load(0xFF00, {0x01});
    registers.a = 1;
    auto expected = registers;
    expected.a = 0xff;
    expected.pc += 2;
    expected.p.n = true;
    expected.p.c = true;
    run<SBCInstruction>(AddressingMode::IMM, 2, expected);

    load(0xFF00, {0xFF});
    registers.a = 127;
    expected = registers;
    expected.pc += 2;
    expected.a = 0x80;
    expected.p.z = false;
    expected.p.n = true;
    expected.p.v = true;
    run<SBCInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, PLATest)
{
    auto expected = registers;
    expected.a = 15;
    expected.pc++;
    push(15);
    run<PLAInstruction>(AddressingMode::IMP, 4, expected);

    expected.a = 128;
    expected.p.n = true;
    expected.pc++;
    push(128);
    run<PLAInstruction>(AddressingMode::IMP, 4, expected);

    expected.p.n = false;
    expected.p.z = true;
    expected.a = 0;
    expected.pc++;
    push(0);
    run<PLAInstruction>(AddressingMode::IMP, 4, expected);
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

TEST_F(InstructionTestFixture, STAZeroPageTest)
{
    STAInstruction instruction(*handler);
    STNZPTest(instruction, registers.a);
}

TEST_F(InstructionTestFixture, STAAbsoluteTest)
{
    STAInstruction instruction(*handler);
    STNABSTest(instruction, registers.a);
}

TEST_F(InstructionTestFixture, STAZeroPageXTest)
{
    STAInstruction instruction(*handler);
    STNZPXYTest(instruction, registers.a, reg::x);
}

TEST_F(InstructionTestFixture, STAIndirectXTest)
{
    load(0xFF00, {0x02});
    registers.x = -1;
    registers.a = 0xB0;
    auto expected = registers;
    expected.pc += 2;
    run<STAInstruction>(AddressingMode::IINDX, 6, expected);
    EXPECT_EQ(0xB0, bus->read(0x01));
}

TEST_F(InstructionTestFixture, STAIndirectYTest)
{
    load(0xFF00, {0x02});
    bus->write(0x02, 0x05);
    registers.y = -1;
    registers.a = 0xB0;
    auto expected = registers;
    expected.pc += 2;
    run<STAInstruction>(AddressingMode::IINDY, 6, expected);
    EXPECT_EQ(0xB0, bus->read(0x04));
}

TEST_F(InstructionTestFixture, STAAbsoluteYTest)
{
    STAInstruction instruction(*handler);
    STNABSXYTest(instruction, registers.a, reg::y);
}

TEST_F(InstructionTestFixture, STAAbsoluteXTest)
{
    STAInstruction instruction(*handler);
    STNABSXYTest(instruction, registers.a, reg::x);
}

TEST_F(InstructionTestFixture, STYZeroPageTest)
{
    STYInstruction instruction(*handler);
    STNZPTest(instruction, registers.y);
}

TEST_F(InstructionTestFixture, STYAbsoluteTest)
{
    STYInstruction instruction(*handler);
    STNABSTest(instruction, registers.y);
}

TEST_F(InstructionTestFixture, STYZeroPageXTest)
{
    STYInstruction instruction(*handler);
    STNZPXYTest(instruction, registers.y, reg::x);
}

TEST_F(InstructionTestFixture, STXZeroPageTest)
{
    STXInstruction instruction(*handler);
    STNZPTest(instruction, registers.x);
}

TEST_F(InstructionTestFixture, STXAbsoluteTest)
{
    STXInstruction instruction(*handler);
    STNABSTest(instruction, registers.x);
}

TEST_F(InstructionTestFixture, STXZeroPageYTest)
{
    STXInstruction instruction(*handler);
    STNZPXYTest(instruction, registers.x, reg::y);
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

TEST_F(InstructionTestFixture, LDYImmediateTest)
{
    LDYInstruction instruction(*handler);
    reg ireg = reg::y;

    LDNImmediateTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDYZeroPageTest)
{
    LDYInstruction instruction(*handler);
    reg ireg = reg::y;

    LDNZeroPageTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDYZeroPageXTest)
{
    LDYInstruction instruction(*handler);
    reg ireg = reg::y;

    LDNZeroPageXYTest(instruction, ireg, reg::x);
}

TEST_F(InstructionTestFixture, LDYAbsoluteTest)
{
    LDYInstruction instruction(*handler);
    reg ireg = reg::y;

    LDNAbsoluteTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDYAbsoluteXTest)
{
    LDYInstruction instruction(*handler);
    reg ireg = reg::y;

    LDNAbsoluteXYTest(instruction, ireg, reg::x);
}

TEST_F(InstructionTestFixture, LDAIndirectXTest)
{
    load(0xFF00, {0x01});
    bus->write(0x02, 0x80);
    
    registers.x = 0x01; // 1 + 1 = 2, load bus->read(2) into registers.a

    auto expected = registers;
    expected.a = 0x80;
    expected.p.n = true;
    expected.pc += 2;
    run<LDAInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x01});
    bus->write(0x02, 0x00);
    expected = registers;
    expected.a = 0x00;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<LDAInstruction>(AddressingMode::IINDX, 6, expected);
}

TEST_F(InstructionTestFixture, LDAIndirectYTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01,0x02);
    bus->write(0xFFFF, 0x80);
    
    registers.y = -3; // 0 - 1 = 0xffff (16bit addressing, 2 - 3 = '-1' aka 0xffff.)

    auto expected = registers;
    expected.a = 0x80;
    expected.p.n = true;
    expected.pc += 2;
    run<LDAInstruction>(AddressingMode::IINDY, 6, expected); // page crossed

    load(0xFF00, {0x01});
    registers.y = 1;
    expected = registers;
    bus->write(0x01, 0x05);
    bus->write(0x06, 0x00);
    registers.a = 0x01; // addr 5 + 1
    expected.a  = 0x00;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<LDAInstruction>(AddressingMode::IINDY, 5, expected);
}

TEST_F(InstructionTestFixture, LDAZeroPageTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNZeroPageTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDAZeroPageXTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNZeroPageXYTest(instruction, ireg, reg::x);
}

TEST_F(InstructionTestFixture, LDAImmediateTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNImmediateTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDAAbsoluteTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNAbsoluteTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDAAbsoluteXTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNAbsoluteXYTest(instruction, ireg, reg::x);
}

TEST_F(InstructionTestFixture, LDAAbsoluteYTest)
{
    LDAInstruction instruction(*handler);
    reg ireg = reg::a;
    LDNAbsoluteXYTest(instruction, ireg, reg::y);
}

TEST_F(InstructionTestFixture, LDXImmediateTest)
{
    LDXInstruction instruction(*handler);
    reg ireg = reg::x;
    LDNImmediateTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDXZeroPageTest)
{
    LDXInstruction instruction(*handler);
    reg ireg = reg::x;
    LDNZeroPageTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDXZeroPageYTest)
{
    LDXInstruction instruction(*handler);
    reg ireg = reg::x;
    LDNZeroPageXYTest(instruction, ireg, reg::y);
}

TEST_F(InstructionTestFixture, LDXAbsoluteTest)
{
    LDXInstruction instruction(*handler);
    reg ireg = reg::x;
    LDNAbsoluteTest(instruction, ireg);
}

TEST_F(InstructionTestFixture, LDXAbsoluteYTest)
{
    LDXInstruction instruction(*handler);
    reg ireg = reg::x;
    LDNAbsoluteXYTest(instruction, ireg, reg::y);
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

TEST_F(InstructionTestFixture, CPXImmediateTest)
{
    load(0xFF00, {16});
    registers.x = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {16});
    registers.x = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {17});
    registers.x = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::IMM, 2, expected);   
}

TEST_F(InstructionTestFixture, CPXZeroPageTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.x = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.x = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 17);
    registers.x = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CPXInstruction>(AddressingMode::ZP, 3, expected);   
}

TEST_F(InstructionTestFixture, CPXAbsoluteTest)
{
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.x = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 3;
    run<CPXInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.x = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 3;
    run<CPXInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 17);
    registers.x = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CPXInstruction>(AddressingMode::ABS, 4, expected);  
}

TEST_F(InstructionTestFixture, CPYImmediateTest)
{
    load(0xFF00, {16});
    registers.y = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {16});
    registers.y = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {17});
    registers.y = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::IMM, 2, expected);   
}

TEST_F(InstructionTestFixture, CPYZeroPageTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.y = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.y = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 17);
    registers.y = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CPYInstruction>(AddressingMode::ZP, 3, expected);   
}

TEST_F(InstructionTestFixture, CPYAbsoluteTest)
{
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.y = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 3;
    run<CPYInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.y = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 3;
    run<CPYInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 17);
    registers.y = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CPYInstruction>(AddressingMode::ABS, 4, expected);  
}

TEST_F(InstructionTestFixture, CMPImmediateTest)
{
    load(0xFF00, {16});
    registers.a = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {16});
    registers.a = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IMM, 2, expected);
    
    load(0xFF00, {17});
    registers.a = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IMM, 2, expected);
}

TEST_F(InstructionTestFixture, CMPZeroPageTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.a = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 16);
    registers.a = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZP, 3, expected);
    
    load(0xFF00, {0x01});
    bus->write(0x01, 17);
    registers.a = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZP, 3, expected);   
}

TEST_F(InstructionTestFixture, CMPAbsoluteTest)
{
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABS, 4, expected);
    
    load(0xFF00, {0xBA, 0xAB});
    bus->write(0xABBA, 17);
    registers.a = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABS, 4, expected);
}

TEST_F(InstructionTestFixture, CMPZeroPageXTest)
{
    load(0xFF00, {0x02});
    bus->write(0x01, 16);
    registers.x = -1;
    registers.a = 16;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZPX, 4, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x01, 16);
    registers.x = -1;
    registers.a = 17;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZPX, 4, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x01, 17);
    registers.x = -1;
    registers.a = 16;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::ZPX, 4, expected); 
}

TEST_F(InstructionTestFixture, CMPAbsoluteXTest)
{
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 16;
    registers.x = -1;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSX, 4, expected);
    
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 17;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSX, 4, expected);
    
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 17);
    registers.a = 16;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSX, 4, expected);

    load(0xFF00, {0x00, 0xAB});
    bus->write(0xAAFF, 17);
    registers.a = 16;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSX, 5, expected);
}

TEST_F(InstructionTestFixture, CMPAbsoluteYTest)
{
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 16;
    registers.y = -1;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSY, 4, expected);
    
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 16);
    registers.a = 17;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSY, 4, expected);
    
    load(0xFF00, {0xBB, 0xAB});
    bus->write(0xABBA, 17);
    registers.a = 16;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSY, 4, expected);

    load(0xFF00, {0x00, 0xAB});
    bus->write(0xAAFF, 17);
    registers.a = 16;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 3;
    run<CMPInstruction>(AddressingMode::ABSY, 5, expected);
}

TEST_F(InstructionTestFixture, CMPIndirectXTest)
{
    load(0xFF00, {0x02});
    bus->write(0x01, 16);
    registers.a = 16;
    registers.x = -1;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDX, 6, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x01, 16);
    registers.a = 17;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDX, 6, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x01, 17);
    registers.a = 16;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDX, 6, expected);

    load(0xFF00, {0x00});
    bus->write(0xFF, 17); // wrap-around within the same page
    registers.a = 16;
    registers.x = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDX, 6, expected);
}

TEST_F(InstructionTestFixture, CMPIndirectYTest)
{
    load(0xFF00, {0x02});
    bus->write(0x02, 0x04);
    bus->write(0x03, 16);
    registers.a = 16;
    registers.y = -1;
    auto expected = registers;
    expected.p.z = true;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDY, 5, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x02, 0x04);
    bus->write(0x03, 16);
    registers.a = 17;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDY, 5, expected);
    
    load(0xFF00, {0x02});
    bus->write(0x02, 0x04);
    bus->write(0x03, 17);
    registers.a = 16;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDY, 5, expected);

    load(0xFF00, {0x10});
    bus->write(0x010, 0x00);
    bus->write(0xFFFF, 17); 
    registers.a = 16;
    registers.y = -1;
    expected = registers;
    expected.p.z = false;
    expected.p.c = false;
    expected.p.n = true;
    expected.pc += 2;
    run<CMPInstruction>(AddressingMode::IINDY, 6, expected);
}

TEST_F(InstructionTestFixture, DECZeroPageTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 0x00);
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 2;
    run<DECInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0xff, bus->read(0x01));

    load(0xFF00, {0x01});
    bus->write(0x01, 0x1);
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<DECInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x00, bus->read(0x01));
}

TEST_F(InstructionTestFixture, DECZeroPageXTest)
{
    load(0xFF00, {0x02});
    bus->write(0x01, 0x00);
    registers.x = -1;
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 2;
    run<DECInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0xff, bus->read(0x01));

    load(0xFF00, {0x02});
    bus->write(0x01, 0x1);
    registers.x = -1;
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<DECInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x01));
}

TEST_F(InstructionTestFixture, DECAbsoluteTest)
{
    load(0xFF00, {0x01, 0x0B});
    bus->write(0x0B01, 0x00);
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 3;
    run<DECInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0xff, bus->read(0x0B01));

    load(0xFF00, {0x01, 0x0B});
    bus->write(0x0B01, 0x1);
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 3;
    run<DECInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x0B01));
}

TEST_F(InstructionTestFixture, DECAbsoluteXTest)
{
    load(0xFF00, {0x02, 0x0B});
    bus->write(0x0B01, 00);
    registers.x = -1;
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 3;
    run<DECInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0xff, bus->read(0x0B01));

    load(0xFF00, {0x02, 0x0B});
    bus->write(0x0B01, 0x01);
    registers.x = -1;
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 3;
    run<DECInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x00, bus->read(0x0B01));
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

TEST_F(InstructionTestFixture, INCZeroPageTest)
{
    load(0xFF00, {0x01});
    bus->write(0x01, 0x7f);
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 2;
    run<INCInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x80, bus->read(0x01));

    load(0xFF00, {0x01});
    bus->write(0x01, 0xff);
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<INCInstruction>(AddressingMode::ZP, 5, expected);
    EXPECT_EQ(0x00, bus->read(0x01));
}

TEST_F(InstructionTestFixture, INCZeroPageXTest)
{
    load(0xFF00, {0x02});
    bus->write(0x01, 0x7f);
    registers.x = -1;
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 2;
    run<INCInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x01));

    load(0xFF00, {0x02});
    bus->write(0x01, 0xff);
    registers.x = -1;
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 2;
    run<INCInstruction>(AddressingMode::ZPX, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x01));
}

TEST_F(InstructionTestFixture, INCAbsoluteTest)
{
    load(0xFF00, {0x01, 0x0B});
    bus->write(0x0B01, 0x7f);
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 3;
    run<INCInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x80, bus->read(0x0B01));

    load(0xFF00, {0x01, 0x0B});
    bus->write(0x0B01, 0xff);
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 3;
    run<INCInstruction>(AddressingMode::ABS, 6, expected);
    EXPECT_EQ(0x00, bus->read(0x0B01));
}

TEST_F(InstructionTestFixture, INCAbsoluteXTest)
{
    load(0xFF00, {0x02, 0x0B});
    bus->write(0x0B01, 0x7f);
    registers.x = -1;
    auto expected = registers;
    expected.p.n = true;
    expected.pc += 3;
    run<INCInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x80, bus->read(0x0B01));

    load(0xFF00, {0x02, 0x0B});
    bus->write(0x0B01, 0xff);
    registers.x = -1;
    expected = registers;
    expected.p.n = false;
    expected.p.z = true;
    expected.pc += 3;
    run<INCInstruction>(AddressingMode::ABSX, 7, expected);
    EXPECT_EQ(0x00, bus->read(0x0B01));
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