#include "nes/bus/bus.h"

namespace nes::bus
{

Bus::Bus()
{

}

nes::peripherals::IPeripheral* Bus::getPeripheral(uint16_t address) const
{
    for(auto* peripheral : _peripherals)
    {
        if(peripheral->inRange(address)) return peripheral;
    } 

    return nullptr;
}

uint8_t Bus::read(uint16_t address) const
{
    auto peripheral = getPeripheral(address);
    if(peripheral != nullptr)
    {
        return peripheral->read(address);
    }
    // todo: decide on behaviour here. rtfm
    return 0; 
}

void Bus::write(uint16_t address, uint8_t value) 
{
    auto peripheral = getPeripheral(address);
    if(peripheral != nullptr)
    {
        peripheral->write(address, value);
    }
}

void Bus::connect(nes::peripherals::IPeripheral& peripheral) 
{
    _peripherals.emplace_back(&peripheral);
}

}