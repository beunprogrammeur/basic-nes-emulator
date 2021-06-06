
#pragma once
#include <nes/cpu/clock/isubscriber_clock_source.h>
#include <vector>

namespace nes::cpu::clock
{
    class DebugClock : public ISubscribingClockSource
    {
    private:
        std::vector<IClockSink*> _sinks;
    public:
        DebugClock();
        virtual void subscribe(IClockSink& sink) override;
        virtual void start() override;
        void start(int ticks);
        virtual void stop() override;
    };
}