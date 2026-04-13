#pragma once

#include "../Common/CSharpCompat.h"
#include "Stat.h"
#include "Enum.h"

namespace Library
{
    class Functions
    {
    public:
        static TimeSpan Max(TimeSpan value1, TimeSpan value2);
        static TimeSpan Min(TimeSpan value1, TimeSpan value2);

        static Element GetElement(const Stats& stats);
        static int GetElement(const Stats& stats, Element& element);
        
        // Additional utility functions would be declared here
        // Based on the C# Functions.cs file (553 lines)
    };
}
