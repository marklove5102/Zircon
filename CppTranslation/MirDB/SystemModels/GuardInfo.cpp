#include "GuardInfo.h"
#include "MapInfo.h"
#include "MonsterInfo.h"

namespace Server::DBModels
{
    void GuardInfo::SetMap(MapInfo* value)
    {
        if (_Map == value) return;

        MapInfo* oldValue = _Map;
        _Map = value;

        OnChanged(oldValue, value, "Map");
    }

    void GuardInfo::SetMonster(MonsterInfo* value)
    {
        if (_Monster == value) return;

        MonsterInfo* oldValue = _Monster;
        _Monster = value;

        OnChanged(oldValue, value, "Monster");
    }

    void GuardInfo::SetX(int value)
    {
        if (_X == value) return;

        int oldValue = _X;
        _X = value;

        OnChanged(oldValue, value, "X");
    }

    void GuardInfo::SetY(int value)
    {
        if (_Y == value) return;

        int oldValue = _Y;
        _Y = value;

        OnChanged(oldValue, value, "Y");
    }

    void GuardInfo::SetDirection(Library::MirDirection value)
    {
        if (_Direction == value) return;

        Library::MirDirection oldValue = _Direction;
        _Direction = value;

        OnChanged(oldValue, value, "Direction");
    }

} // namespace Server::DBModels
