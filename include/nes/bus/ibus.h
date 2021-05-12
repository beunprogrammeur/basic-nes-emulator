#pragma once

#include <stdint.h>
#include "nes/peripherals/iperipheral.h"

namespace nes::bus
{

class IBus
{
public:
    virtual uint8_t read(uint16_t address) const = 0;
    virtual void    write(uint16_t address, uint8_t value) = 0;
    virtual void    connect(nes::peripherals::IPeripheral& peripheral) = 0;
};

}