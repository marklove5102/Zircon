#include "RespawnInfo.h"
#include "MonsterInfo.h"
#include "MapInfo.h"

namespace Server::DBModels
{
    void RespawnInfo::SetMonster(MonsterInfo* value)
    {
        if (_Monster == value) return;

        auto oldValue = _Monster;
        _Monster = value;

        OnChanged(oldValue, value, "Monster");
    }

    void RespawnInfo::SetMap(MapInfo* value)
    {
        if (_Map == value) return;

        auto oldValue = _Map;
        _Map = value;

        OnChanged(oldValue, value, "Map");
    }

    void RespawnInfo::SetX(int value)
    {
        if (_X == value) return;

        auto oldValue = _X;
        _X = value;

        OnChanged(oldValue, value, "X");
    }

    void RespawnInfo::SetY(int value)
    {
        if (_Y == value) return;

        auto oldValue = _Y;
        _Y = value;

        OnChanged(oldValue, value, "Y");
    }

    void RespawnInfo::SetDelay(int value)
    {
        if (_Delay == value) return;

        auto oldValue = _Delay;
        _Delay = value;

        OnChanged(oldValue, value, "Delay");
    }

    void RespawnInfo::SetSpread(int value)
    {
        if (_Spread == value) return;

        auto oldValue = _Spread;
        _Spread = value;

        OnChanged(oldValue, value, "Spread");
    }

    void RespawnInfo::SetCount(int value)
    {
        if (_Count == value) return;

        auto oldValue = _Count;
        _Count = value;

        OnChanged(oldValue, value, "Count");
    }

    void RespawnInfo::SetDropSet(int value)
    {
        if (_DropSet == value) return;

        auto oldValue = _DropSet;
        _DropSet = value;

        OnChanged(oldValue, value, "DropSet");
    }
}
