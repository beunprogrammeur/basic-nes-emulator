#include <nes/cpu/clock/debug_clock.h>

namespace nes::cpu::clock
{
DebugClock::DebugClock()
{
}

void DebugClock::subscribe(IClockSink& sink)
{
    _sinks.emplace_back(&sink);
}

void DebugClock::start()
{
    for(auto& sink : _sinks)
    {
        sink->tick();
    }
}

void DebugClock::start(int ticks)
{
    for(int i = 0; i < ticks; i++)
    {
        start();
    }
}

void DebugClock::stop()
{
    // not needed for the debug clock
}
}
