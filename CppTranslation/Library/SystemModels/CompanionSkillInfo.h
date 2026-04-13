#pragma once
#include "MirDB/DBObject.h"
#include "Enum.h"

namespace Library::SystemModels
{
    public sealed class CompanionSkillInfo : public DBObject
    {
    public:
        PROPERTY(int, Level);
        PROPERTY(Stat, StatType);
        PROPERTY(int, MaxAmount);
        PROPERTY(int, Weight);
    };
}
