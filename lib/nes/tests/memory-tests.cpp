#include <gtest/gtest.h>
#include <nes/peripherals/memory.h>

class MemoryTestFixture : public testing::Test
{
protected:
    nes::peripherals::Memory* memory;
    nes::peripherals::Memory* romemory;

    void SetUp() override
    {
        memory = new nes::peripherals::Memory(10, 10, false);
        romemory = new nes::peripherals::Memory(10, 10, true);
    }

    void TearDown() override
    {
        delete memory;
        delete romemory;
        memory = nullptr;
        romemory = nullptr;
    }
};

TEST_F(MemoryTestFixture, canWriteToMemory)
{
    memory->write(15, 66);
    ASSERT_EQ(66, memory->read(15));
}

TEST_F(MemoryTestFixture, cantWriteToReadOnlyMemory)
{
    memory->write(15, 66);
    ASSERT_EQ(66, memory->read(15));
}

TEST_F(MemoryTestFixture, WriteOutOfBoundsDoesntDoAnything)
{
    memory->write(1000, 10);
    ASSERT_EQ(0, memory->read(1000));
}

TEST_F(MemoryTestFixture, ReadOutOfBoundsReturnsZero)
{
    ASSERT_EQ(0, memory->read(9001));
}