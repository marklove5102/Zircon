#include "MonsterInfo.h"

namespace Server::DBModels
{
    void MonsterInfo::SetMonsterName(const std::string& value)
    {
        if (_MonsterName == value) return;
        std::string oldValue = _MonsterName;
        _MonsterName = value;
        OnChanged(oldValue, value, "MonsterName");
    }

    void MonsterInfo::SetImage(Library::MonsterImage value)
    {
        if (_Image == value) return;
        Library::MonsterImage oldValue = _Image;
        _Image = value;
        OnChanged(oldValue, value, "Image");
    }

    void MonsterInfo::SetAI(int value)
    {
        if (_AI == value) return;
        int oldValue = _AI;
        _AI = value;
        OnChanged(oldValue, value, "AI");
    }

    void MonsterInfo::SetLevel(int value)
    {
        if (_Level == value) return;
        int oldValue = _Level;
        _Level = value;
        OnChanged(oldValue, value, "Level");
    }

    void MonsterInfo::SetViewRange(int value)
    {
        if (_ViewRange == value) return;
        int oldValue = _ViewRange;
        _ViewRange = value;
        OnChanged(oldValue, value, "ViewRange");
    }

    void MonsterInfo::SetCoolEye(int value)
    {
        if (_CoolEye == value) return;
        int oldValue = _CoolEye;
        _CoolEye = value;
        OnChanged(oldValue, value, "CoolEye");
    }

    void MonsterInfo::SetExperience(double value)
    {
        if (_Experience == value) return;
        double oldValue = _Experience;
        _Experience = value;
        OnChanged(oldValue, value, "Experience");
    }

    void MonsterInfo::SetUndead(bool value)
    {
        if (_Undead == value) return;
        bool oldValue = _Undead;
        _Undead = value;
        OnChanged(oldValue, value, "Undead");
    }

    void MonsterInfo::SetCanPush(bool value)
    {
        if (_CanPush == value) return;
        bool oldValue = _CanPush;
        _CanPush = value;
        OnChanged(oldValue, value, "CanPush");
    }

    void MonsterInfo::SetAttackDelay(int value)
    {
        if (_AttackDelay == value) return;
        int oldValue = _AttackDelay;
        _AttackDelay = value;
        OnChanged(oldValue, value, "AttackDelay");
    }

    void MonsterInfo::SetMoveDelay(int value)
    {
        if (_MoveDelay == value) return;
        int oldValue = _MoveDelay;
        _MoveDelay = value;
        OnChanged(oldValue, value, "MoveDelay");
    }

    void MonsterInfo::SetIsBoss(bool value)
    {
        if (_IsBoss == value) return;
        bool oldValue = _IsBoss;
        _IsBoss = value;
        OnChanged(oldValue, value, "IsBoss");
    }

    void MonsterInfo::SetMonsterInfoStats(DBBindingList<MonsterInfoStat>* value)
    {
        if (_MonsterInfoStats == value) return;
        DBBindingList<MonsterInfoStat>* oldValue = _MonsterInfoStats;
        _MonsterInfoStats = value;
        OnChanged(oldValue, value, "MonsterInfoStats");
    }

    void MonsterInfo::SetRespawns(DBBindingList<RespawnInfo>* value)
    {
        if (_Respawns == value) return;
        DBBindingList<RespawnInfo>* oldValue = _Respawns;
        _Respawns = value;
        OnChanged(oldValue, value, "Respawns");
    }

    void MonsterInfo::SetDrops(DBBindingList<DropInfo>* value)
    {
        if (_Drops == value) return;
        DBBindingList<DropInfo>* oldValue = _Drops;
        _Drops = value;
        OnChanged(oldValue, value, "Drops");
    }

    void MonsterInfo::OnCreated()
    {
        DBObject::OnCreated();
        SetCanPush(true);
        SetViewRange(7);
        SetAttackDelay(2500);
        SetMoveDelay(1800);
    }

    void MonsterInfo::OnLoaded()
    {
        DBObject::OnLoaded();
        StatsChanged();
    }

    void MonsterInfo::StatsChanged()
    {
        Stats.Clear();
        if (_MonsterInfoStats)
        {
            for (auto* stat : *_MonsterInfoStats)
                Stats[stat->GetStat()] += stat->GetAmount();
        }
    }
} // namespace Server::DBModels
