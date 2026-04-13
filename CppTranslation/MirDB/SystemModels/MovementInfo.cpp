#include "MovementInfo.h"
#include "MapInfo.h"

namespace Server::DBModels
{
    void MovementInfo::SetSourceMap(MapInfo* value)
    {
        if (_SourceMap == value) return;
        MapInfo* oldValue = _SourceMap;
        _SourceMap = value;
        OnChanged(oldValue, value, "SourceMap");
    }

    void MovementInfo::SetSourceX(int value)
    {
        if (_SourceX == value) return;
        int oldValue = _SourceX;
        _SourceX = value;
        OnChanged(oldValue, value, "SourceX");
    }

    void MovementInfo::SetSourceY(int value)
    {
        if (_SourceY == value) return;
        int oldValue = _SourceY;
        _SourceY = value;
        OnChanged(oldValue, value, "SourceY");
    }

    void MovementInfo::SetDestinationMap(MapInfo* value)
    {
        if (_DestinationMap == value) return;
        MapInfo* oldValue = _DestinationMap;
        _DestinationMap = value;
        OnChanged(oldValue, value, "DestinationMap");
    }

    void MovementInfo::SetDestinationX(int value)
    {
        if (_DestinationX == value) return;
        int oldValue = _DestinationX;
        _DestinationX = value;
        OnChanged(oldValue, value, "DestinationX");
    }

    void MovementInfo::SetDestinationY(int value)
    {
        if (_DestinationY == value) return;
        int oldValue = _DestinationY;
        _DestinationY = value;
        OnChanged(oldValue, value, "DestinationY");
    }

    void MovementInfo::SetMapIcon(Library::MapIcon value)
    {
        if (_MapIcon == value) return;
        Library::MapIcon oldValue = _MapIcon;
        _MapIcon = value;
        OnChanged(oldValue, value, "MapIcon");
    }
} // namespace Server::DBModels
