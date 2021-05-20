#pragma once

namespace nes::cpu::clock
{
    class IClockSink
    {
    public:
        virtual void tick() = 0;
    };
}