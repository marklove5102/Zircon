#pragma once
#include "MirDB/DBObject.h"
#include "Enum.h"

namespace Library::SystemModels
{
    class MapRegion;
    class ItemInfo;
    class RespawnInfo;

    public sealed class MovementInfo : public DBObject
    {
    public:
        PROPERTY(MapRegion*, SourceRegion);
        PROPERTY(MapRegion*, DestinationRegion);
        PROPERTY(MapIcon, Icon);
        PROPERTY(ItemInfo*, NeedItem);
        PROPERTY(RespawnInfo*, NeedSpawn);
        PROPERTY(MovementEffect, Effect);
        PROPERTY(RequiredClass, RequiredClass);
        
    protected:
        void OnCreated() override;
    };
}
