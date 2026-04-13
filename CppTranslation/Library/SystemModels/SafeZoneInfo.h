#pragma once

#include "../MirDB/DBObject.h"
#include "MapRegion.h"
#include "../Enum.h"
#include <vector>

namespace Library::SystemModels
{

class SafeZoneInfo : public DBObject
{
private:
    MapRegion* _Region;
    MapRegion* _BindRegion;
    RequiredClass _StartClass;
    bool _RedZone;

public:
    MapRegion* GetRegion() const { return _Region; }
    void SetRegion(MapRegion* value);

    MapRegion* GetBindRegion() const { return _BindRegion; }
    void SetBindRegion(MapRegion* value);

    RequiredClass GetStartClass() const { return _StartClass; }
    void SetStartClass(RequiredClass value);

    bool GetRedZone() const { return _RedZone; }
    void SetRedZone(bool value);

    std::vector<Point> ValidBindPoints;
};

} // namespace Library::SystemModels
