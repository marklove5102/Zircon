#pragma once

#include "../MirDB/DBObject.h"
#include "MonsterInfo.h"
#include "RespawnInfo.h"
#include "MapRegion.h"
#include "MapInfo.h"
#include <string>
#include <vector>

namespace Library::SystemModels
{

enum class EventActionType : uint8_t
{
    None,
    GlobalMessage,
    MapMessage,
    PlayerMessage,
    MonsterSpawn,
    MonsterPlayerSpawn,
    MovementSettings,
    PlayerRecall,
    PlayerEscape,
};

class EventTarget;
class EventAction;

class EventInfo : public DBObject
{
private:
    std::string _Description;
    int _MaxValue;
    std::vector<EventTarget*> Targets;
    std::vector<EventAction*> Actions;

public:
    std::string GetDescription() const { return _Description; }
    void SetDescription(const std::string& value);

    int GetMaxValue() const { return _MaxValue; }
    void SetMaxValue(int value);

    std::vector<EventTarget*>& GetTargets() { return Targets; }
    const std::vector<EventTarget*>& GetTargets() const { return Targets; }

    std::vector<EventAction*>& GetActions() { return Actions; }
    const std::vector<EventAction*>& GetActions() const { return Actions; }

    int CurrentValue; // Server Variable
};

class EventTarget : public DBObject
{
private:
    EventInfo* _Event;
    MonsterInfo* _Monster;
    int _DropSet;
    int _Value;

public:
    EventInfo* GetEvent() const { return _Event; }
    void SetEvent(EventInfo* value);

    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);

    int GetDropSet() const { return _DropSet; }
    void SetDropSet(int value);

    int GetValue() const { return _Value; }
    void SetValue(int value);
};

class EventAction : public DBObject
{
private:
    EventInfo* _Event;
    int _TriggerValue;
    EventActionType _Type;
    std::string _StringParameter1;
    MonsterInfo* _MonsterParameter1;
    RespawnInfo* _RespawnParameter1;
    MapRegion* _RegionParameter1;
    MapInfo* _MapParameter1;

public:
    EventInfo* GetEvent() const { return _Event; }
    void SetEvent(EventInfo* value);

    int GetTriggerValue() const { return _TriggerValue; }
    void SetTriggerValue(int value);

    EventActionType GetType() const { return _Type; }
    void SetType(EventActionType value);

    std::string GetStringParameter1() const { return _StringParameter1; }
    void SetStringParameter1(const std::string& value);

    MonsterInfo* GetMonsterParameter1() const { return _MonsterParameter1; }
    void SetMonsterParameter1(MonsterInfo* value);

    RespawnInfo* GetRespawnParameter1() const { return _RespawnParameter1; }
    void SetRespawnParameter1(RespawnInfo* value);

    MapRegion* GetRegionParameter1() const { return _RegionParameter1; }
    void SetRegionParameter1(MapRegion* value);

    MapInfo* GetMapParameter1() const { return _MapParameter1; }
    void SetMapParameter1(MapInfo* value);
};

} // namespace Library::SystemModels
