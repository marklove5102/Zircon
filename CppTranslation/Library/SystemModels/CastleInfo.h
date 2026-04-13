#pragma once

#include "../MirDB/DBObject.h"
#include "MapInfo.h"
#include "MapRegion.h"
#include "ItemInfo.h"
#include "MonsterInfo.h"
#include <string>

namespace Library::SystemModels
{

class CastleInfo : public DBObject
{
private:
    std::string _Name;
    MapInfo* _Map;
    TimeSpan _StartTime;
    TimeSpan _Duration;
    MapRegion* _CastleRegion;
    MapRegion* _AttackSpawnRegion;
    ItemInfo* _Item;
    MonsterInfo* _Monster;
    decimal _Discount;

public:
    std::string GetName() const { return _Name; }
    void SetName(const std::string& value);

    MapInfo* GetMap() const { return _Map; }
    void SetMap(MapInfo* value);

    TimeSpan GetStartTime() const { return _StartTime; }
    void SetStartTime(TimeSpan value);

    TimeSpan GetDuration() const { return _Duration; }
    void SetDuration(TimeSpan value);

    MapRegion* GetCastleRegion() const { return _CastleRegion; }
    void SetCastleRegion(MapRegion* value);

    MapRegion* GetAttackSpawnRegion() const { return _AttackSpawnRegion; }
    void SetAttackSpawnRegion(MapRegion* value);

    ItemInfo* GetItem() const { return _Item; }
    void SetItem(ItemInfo* value);

    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);

    decimal GetDiscount() const { return _Discount; }
    void SetDiscount(decimal value);

    DateTime WarDate;
};

} // namespace Library::SystemModels
