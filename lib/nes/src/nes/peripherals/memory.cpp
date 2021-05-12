#include "nes/peripherals/memory.h"

namespace nes::peripherals
{
    Memory::Memory(uint16_t startAddress, uint16_t addressSpace, bool readOnly)
        : _startAddress(startAddress), _addressSpace(addressSpace), _readOnly(readOnly), _memory()
    {
        _memory.reserve(_addressSpace);
    }

    uint8_t  Memory::read(uint16_t address) const
    {
        if(!inRange(address)) return 0;
        return _memory[address - _startAddress];
    }

    void     Memory::write(uint16_t address, uint8_t value)
    {
        if(_readOnly || !inRange(address)) return;
        _memory[address - _startAddress] = value;
    }
}