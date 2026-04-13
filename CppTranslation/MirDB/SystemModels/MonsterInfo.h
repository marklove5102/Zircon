#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"
#include "../DBBindingList.h"

namespace Server::DBModels
{
    class MonsterInfoStat;
    class RespawnInfo;
    class DropInfo;

    class MonsterInfo : public DBObject
    {
    private:
        std::string _MonsterName;
        Library::MonsterImage _Image = Library::MonsterImage::None;
        int _AI = 0;
        int _Level = 0;
        int _ViewRange = 7;
        int _CoolEye = 0;
        double _Experience = 0.0;
        bool _Undead = false;
        bool _CanPush = true;
        int _AttackDelay = 2500;
        int _MoveDelay = 1800;
        bool _IsBoss = false;

        DBBindingList<MonsterInfoStat>* _MonsterInfoStats = nullptr;
        DBBindingList<RespawnInfo>* _Respawns = nullptr;
        DBBindingList<DropInfo>* _Drops = nullptr;

    public:
        Library::Stats Stats;

        std::string GetMonsterName() const { return _MonsterName; }
        void SetMonsterName(const std::string& value);

        Library::MonsterImage GetImage() const { return _Image; }
        void SetImage(Library::MonsterImage value);

        int GetAI() const { return _AI; }
        void SetAI(int value);

        int GetLevel() const { return _Level; }
        void SetLevel(int value);

        int GetViewRange() const { return _ViewRange; }
        void SetViewRange(int value);

        int GetCoolEye() const { return _CoolEye; }
        void SetCoolEye(int value);

        double GetExperience() const { return _Experience; }
        void SetExperience(double value);

        bool GetUndead() const { return _Undead; }
        void SetUndead(bool value);

        bool GetCanPush() const { return _CanPush; }
        void SetCanPush(bool value);

        int GetAttackDelay() const { return _AttackDelay; }
        void SetAttackDelay(int value);

        int GetMoveDelay() const { return _MoveDelay; }
        void SetMoveDelay(int value);

        bool GetIsBoss() const { return _IsBoss; }
        void SetIsBoss(bool value);

        // Association("MonsterInfoStats", true)
        DBBindingList<MonsterInfoStat>* GetMonsterInfoStats() const { return _MonsterInfoStats; }
        void SetMonsterInfoStats(DBBindingList<MonsterInfoStat>* value);

        // Association("Respawns", true)
        DBBindingList<RespawnInfo>* GetRespawns() const { return _Respawns; }
        void SetRespawns(DBBindingList<RespawnInfo>* value);

        // Association("Drops", true)
        DBBindingList<DropInfo>* GetDrops() const { return _Drops; }
        void SetDrops(DBBindingList<DropInfo>* value);

    protected:
        void OnCreated() override;
        void OnLoaded() override;

    public:
        void StatsChanged();
    };

} // namespace Server::DBModels
