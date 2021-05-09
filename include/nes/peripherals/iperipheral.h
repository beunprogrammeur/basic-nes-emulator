#pragma once

#include <stdint.h>

namespace nes::peripherals
{

class IPeripheral
{
public:
    // the firs address that this peripheral listens to
    virtual uint16_t startAddress() const = 0;
    // the amount of space is managed by this peripheral
    virtual uint16_t addressSpace() const = 0;
    // whether the given address lays within this peripherals memory space
    virtual bool    inRange(uint16_t address) const = 0;
    // reads a byte from the address space
    virtual uint8_t read(uint16_t address) const = 0;
    // write a byte to the address space
    virtual void    write(uint16_t address, uint8_t value) = 0;
};

}