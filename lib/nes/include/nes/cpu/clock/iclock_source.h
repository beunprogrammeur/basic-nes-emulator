#pragma once

namespace nes::cpu::clock
{
    class IClockSource
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}