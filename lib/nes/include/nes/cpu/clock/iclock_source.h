#pragma once
#include <nes/cpu/clock/iclock_sink.h>

namespace nes::cpu::clock
{
    class IClockSource
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void addSink(IClockSink& sink);
    };
}