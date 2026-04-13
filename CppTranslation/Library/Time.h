#pragma once

#include <chrono>
#include "LibraryCore/Globals.h"

namespace Library
{
    class Time
    {
    private:
        static const std::chrono::steady_clock::time_point StartTime;
        static std::chrono::steady_clock::duration GetElapsed();

    public:
        static DateTime Now();
    };
}
