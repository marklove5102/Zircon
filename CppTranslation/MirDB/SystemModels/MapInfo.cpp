#include "MapInfo.h"

namespace Server::DBModels
{
    void MapInfo::SetFileName(const std::string& value)
    {
        if (_FileName == value) return;
        std::string oldValue = _FileName;
        _FileName = value;
        OnChanged(oldValue, value, "FileName");
    }

    void MapInfo::SetDescription(const std::string& value)
    {
        if (_Description == value) return;
        std::string oldValue = _Description;
        _Description = value;
        OnChanged(oldValue, value, "Description");
    }

    void MapInfo::SetMiniMap(int value)
    {
        if (_MiniMap == value) return;
        int oldValue = _MiniMap;
        _MiniMap = value;
        OnChanged(oldValue, value, "MiniMap");
    }

    void MapInfo::SetLight(Library::LightSetting value)
    {
        if (_Light == value) return;
        Library::LightSetting oldValue = _Light;
        _Light = value;
        OnChanged(oldValue, value, "Light");
    }

    void MapInfo::SetAllowRT(bool value)
    {
        if (_AllowRT == value) return;
        bool oldValue = _AllowRT;
        _AllowRT = value;
        OnChanged(oldValue, value, "AllowRT");
    }

    void MapInfo::SetSafeZones(DBBindingList<SafeZoneInfo>* value)
    {
        if (_SafeZones == value) return;
        DBBindingList<SafeZoneInfo>* oldValue = _SafeZones;
        _SafeZones = value;
        OnChanged(oldValue, value, "SafeZones");
    }

    void MapInfo::SetMovements(DBBindingList<MovementInfo>* value)
    {
        if (_Movements == value) return;
        DBBindingList<MovementInfo>* oldValue = _Movements;
        _Movements = value;
        OnChanged(oldValue, value, "Movements");
    }

    void MapInfo::SetRespawns(DBBindingList<RespawnInfo>* value)
    {
        if (_Respawns == value) return;
        DBBindingList<RespawnInfo>* oldValue = _Respawns;
        _Respawns = value;
        OnChanged(oldValue, value, "Respawns");
    }

    void MapInfo::SetNPCs(DBBindingList<NPCInfo>* value)
    {
        if (_NPCs == value) return;
        DBBindingList<NPCInfo>* oldValue = _NPCs;
        _NPCs = value;
        OnChanged(oldValue, value, "NPCs");
    }

    void MapInfo::SetGuards(DBBindingList<GuardInfo>* value)
    {
        if (_Guards == value) return;
        DBBindingList<GuardInfo>* oldValue = _Guards;
        _Guards = value;
        OnChanged(oldValue, value, "Guards");
    }

    void MapInfo::OnCreated()
    {
        DBObject::OnCreated();
        SetAllowRT(true);
    }
} // namespace Server::DBModels
