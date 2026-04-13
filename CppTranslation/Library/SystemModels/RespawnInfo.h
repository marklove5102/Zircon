#pragma once

#include "../MirDB/DBObject.h"
#include "MonsterInfo.h"
#include "MapRegion.h"
#include <string>

namespace Library::SystemModels
{

class RespawnInfo : public DBObject
{
private:
    MonsterInfo* _Monster;
    MapRegion* _Region;
    bool _EventSpawn;
    int _Delay;
    int _Count;
    int _DropSet;
    bool _Announce;
    int _EasterEventChance;

public:
    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);

    MapRegion* GetRegion() const { return _Region; }
    void SetRegion(MapRegion* value);

    bool GetEventSpawn() const { return _EventSpawn; }
    void SetEventSpawn(bool value);

    int GetDelay() const { return _Delay; }
    void SetDelay(int value);

    int GetCount() const { return _Count; }
    void SetCount(int value);

    int GetDropSet() const { return _DropSet; }
    void SetDropSet(int value);

    bool GetAnnounce() const { return _Announce; }
    void SetAnnounce(bool value);

    int GetEasterEventChance() const { return _EasterEventChance; }
    void SetEasterEventChance(int value);

    // Computed properties (IgnoreProperty in C#)
    std::string GetRegionName() const;
    std::string GetMonsterName() const;
};

} // namespace Library::SystemModels
