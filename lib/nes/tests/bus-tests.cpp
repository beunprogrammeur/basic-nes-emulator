#include <gtest/gtest.h>
#include <vector>

#include <nes/bus/bus.h>

class BusTestFixture : public testing::Test
{
protected:
    nes::bus::IBus* bus;
    
    void SetUp() override
    {
        bus = new nes::bus::Bus;
    }

    void TearDown() override
    {
        delete bus;
        bus = nullptr;
    }
};

class MockPeripheral : public nes::peripherals::IPeripheral
{
private:
    static const int _size = 10;
    uint16_t _startAddress;
    uint8_t _space[_size];
public:
    MockPeripheral(uint16_t startAddress) : _startAddress(startAddress), _space{0} { for(int i = 0; i < addressSpace(); i++) _space[i] = 0; }
    uint16_t startAddress() const override            { return _startAddress; }
    uint16_t addressSpace() const override            { return _size; }
    bool     inRange(uint16_t address) const override { return address >= _startAddress && address < _startAddress + addressSpace(); }
    
    uint8_t  read(uint16_t address) const override    { 
        if(!inRange(address)) return 0;
        return _space[address - _startAddress];  
    }
    
    void     write(uint16_t address, uint8_t value) override  { 
        if(!inRange(address)) return;
        _space[address - _startAddress] = value; 
    }
};

TEST(MockPeripheralTests, MockPeripheralBasicFunctionalityWorks)
{
    MockPeripheral mp(0);
    mp.write(0, 16);
    ASSERT_EQ(16, mp.read(0));

    mp.write(9, 17);
    ASSERT_EQ(17, mp.read(9));

    ASSERT_FALSE(mp.inRange(10));
}

TEST_F(BusTestFixture, WriteToPeripheral)
{
    MockPeripheral mp1(0);
    MockPeripheral mp2(10);
    bus->connect(mp1);
    bus->connect(mp2);

    bus->write(0,  12);
    bus->write(10, 13);
    bus->write(9,  14);
    bus->write(19, 15);

    ASSERT_EQ(12, mp1.read(0));
    ASSERT_EQ(13, mp2.read(10));
    ASSERT_EQ(14, mp1.read(9));
    ASSERT_EQ(15, mp2.read(19));
}

TEST_F(BusTestFixture, ReadFromPeriperhal)
{
    MockPeripheral mp1(0);
    MockPeripheral mp2(10);
    bus->connect(mp1);
    bus->connect(mp2);

    mp1.write(0, 5);
    mp1.write(9, 6);
    mp2.write(10, 7);
    mp2.write(19, 8);

    ASSERT_EQ(5, bus->read(0));
    ASSERT_EQ(6, bus->read(9));
    ASSERT_EQ(7, bus->read(10));
    ASSERT_EQ(8, bus->read(19));
}

TEST_F(BusTestFixture, ReadWriteOutOfBounds)
{
    MockPeripheral mp1(0);
    bus->connect(mp1);

    bus->write(100, 10);
    ASSERT_EQ(0, bus->read(100));
}