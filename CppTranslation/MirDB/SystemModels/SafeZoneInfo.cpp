#include "SafeZoneInfo.h"
#include "MapInfo.h"

namespace Server::DBModels
{
    void SafeZoneInfo::SetMap(MapInfo* value)
    {
        if (_Map == value) return;

        auto oldValue = _Map;
        _Map = value;

        OnChanged(oldValue, value, "Map");
    }

    void SafeZoneInfo::SetX(int value)
    {
        if (_X == value) return;

        auto oldValue = _X;
        _X = value;

        OnChanged(oldValue, value, "X");
    }

    void SafeZoneInfo::SetY(int value)
    {
        if (_Y == value) return;

        auto oldValue = _Y;
        _Y = value;

        OnChanged(oldValue, value, "Y");
    }

    void SafeZoneInfo::SetSize(int value)
    {
        if (_Size == value) return;

        auto oldValue = _Size;
        _Size = value;

        OnChanged(oldValue, value, "Size");
    }

    void SafeZoneInfo::SetBindPoint(bool value)
    {
        if (_BindPoint == value) return;

        auto oldValue = _BindPoint;
        _BindPoint = value;

        OnChanged(oldValue, value, "BindPoint");
    }

    void SafeZoneInfo::SetStartClass(RequiredClass value)
    {
        if (_StartClass == value) return;

        auto oldValue = _StartClass;
        _StartClass = value;

        OnChanged(oldValue, value, "StartClass");
    }
}
