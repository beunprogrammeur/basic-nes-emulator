#pragma once
#include "ipheripheral.h"
#include <vector>

namespace nes::peripherals
{
class Memory : public IPeripheral
{
private:
    uint16_t _startAddress;
    uint16_t _addressSpace;
    bool _readOnly;
    std::vector<uint8_t> _memory;

public:
    Memory(uint16_t startAddress, uint16_t addressSpace, bool readOnly);
    // the firs address that this peripheral listens to
    uint16_t startAddress() const override { return _startAddress; }
    // the amount of space is managed by this peripheral
    uint16_t addressSpace() const override { return _addressSpace; }
    // whether the given address lays within this peripherals memory space
    bool    inRange(uint16_t address) const override{ return address >= _startAddress && address < _startAddress + _addressSpace; }
    // reads a byte from the address space
    uint8_t read(uint16_t address) const override;
    // write a byte to the address space
    void    write(uint16_t address, uint8_t value) override;
};
}