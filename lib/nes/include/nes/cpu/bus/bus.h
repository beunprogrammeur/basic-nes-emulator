#pragma once

#include <vector>
#include <nes/cpu/bus/ibus.h>

namespace nes::peripherals
{
    class IPeripheral;
}

namespace nes::cpu::bus
{

class Bus : public IBus
{
private:
    std::vector<nes::peripherals::IPeripheral*> _peripherals;
public:
    Bus();
    uint8_t read(uint16_t address) const override;
    void    write(uint16_t address, uint8_t value) override;
    void    connect(nes::peripherals::IPeripheral& peripheral) override;

private:
    nes::peripherals::IPeripheral* getPeripheral(uint16_t address) const;
};

}