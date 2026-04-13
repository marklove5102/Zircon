#pragma once
#include "MirDB/DBObject.h"

namespace Library::SystemModels
{
    public sealed class CompanionLevelInfo : public DBObject
    {
    public:
        PROPERTY(int, Level);
        PROPERTY(int, MaxExperience);
        PROPERTY(int, InventorySpace);
        PROPERTY(int, InventoryWeight);
        PROPERTY(int, MaxHunger);
    };
}
