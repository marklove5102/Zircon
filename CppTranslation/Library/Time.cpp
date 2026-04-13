#include "Time.h"
#include <chrono>

namespace Library
{
    const std::chrono::steady_clock::time_point Time::StartTime = std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration Time::GetElapsed()
    {
        return std::chrono::steady_clock::now() - StartTime;
    }

    DateTime Time::Now()
    {
        auto elapsed = GetElapsed();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        return DateTime(DateTime::UnixEpoch) + TimeSpan::FromMilliseconds(ms);
    }
}
