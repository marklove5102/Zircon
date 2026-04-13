#pragma once
#include "MirDB/DBObject.h"

namespace Library::SystemModels
{
    class MapInfo;
    class ItemInfo;

    public sealed class MineInfo : public DBObject
    {
    public:
        PROPERTY(MapInfo*, Map);
        PROPERTY(ItemInfo*, Item);
        PROPERTY(int, Chance);
    };
}
