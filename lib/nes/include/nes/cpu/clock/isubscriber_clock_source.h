#pragma once
#include <nes/cpu/clock/iclock_source.h>
#include <nes/cpu/clock/iclock_sink.h>

namespace nes::cpu::clock
{
    class ISubscribingClockSource : public IClockSource
    {
    public:
        virtual void subscribe(IClockSink& sink) = 0;
    };
}