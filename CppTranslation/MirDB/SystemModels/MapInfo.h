#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"
#include "../DBBindingList.h"

namespace Server::DBModels
{
    class SafeZoneInfo;
    class MovementInfo;
    class RespawnInfo;
    class NPCInfo;
    class GuardInfo;

    class MapInfo : public DBObject
    {
    private:
        std::string _FileName;
        std::string _Description;
        int _MiniMap = 0;
        Library::LightSetting _Light = Library::LightSetting::Normal;
        bool _AllowRT = true;

        DBBindingList<SafeZoneInfo>* _SafeZones = nullptr;
        DBBindingList<MovementInfo>* _Movements = nullptr;
        DBBindingList<RespawnInfo>* _Respawns = nullptr;
        DBBindingList<NPCInfo>* _NPCs = nullptr;
        DBBindingList<GuardInfo>* _Guards = nullptr;

    public:
        std::string GetFileName() const { return _FileName; }
        void SetFileName(const std::string& value);

        std::string GetDescription() const { return _Description; }
        void SetDescription(const std::string& value);

        int GetMiniMap() const { return _MiniMap; }
        void SetMiniMap(int value);

        Library::LightSetting GetLight() const { return _Light; }
        void SetLight(Library::LightSetting value);

        bool GetAllowRT() const { return _AllowRT; }
        void SetAllowRT(bool value);

        // Association("SafeZones", true)
        DBBindingList<SafeZoneInfo>* GetSafeZones() const { return _SafeZones; }
        void SetSafeZones(DBBindingList<SafeZoneInfo>* value);

        // Association("Movements", true)
        DBBindingList<MovementInfo>* GetMovements() const { return _Movements; }
        void SetMovements(DBBindingList<MovementInfo>* value);

        // Association("Respawns", true)
        DBBindingList<RespawnInfo>* GetRespawns() const { return _Respawns; }
        void SetRespawns(DBBindingList<RespawnInfo>* value);

        // Association("NPCs", true)
        DBBindingList<NPCInfo>* GetNPCs() const { return _NPCs; }
        void SetNPCs(DBBindingList<NPCInfo>* value);

        // Association("Guards", true)
        DBBindingList<GuardInfo>* GetGuards() const { return _Guards; }
        void SetGuards(DBBindingList<GuardInfo>* value);

    protected:
        void OnCreated() override;
    };

} // namespace Server::DBModels
