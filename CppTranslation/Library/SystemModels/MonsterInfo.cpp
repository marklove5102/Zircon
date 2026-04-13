#include "MonsterInfo.h"
#include "MonsterInfoStat.h"
#include "RespawnInfo.h"
#include "DropInfo.h"

namespace Library { namespace SystemModels {

void MonsterInfo::SetMonsterName(const std::string& value)
{
    if (_MonsterName == value) return;
    
    auto oldValue = _MonsterName;
    _MonsterName = value;
    OnChanged(oldValue, value, "MonsterName");
}

void MonsterInfo::SetImage(MonsterImage value)
{
    if (_Image == value) return;
    
    auto oldValue = _Image;
    _Image = value;
    OnChanged(oldValue, value, "Image");
}

void MonsterInfo::SetAI(int value)
{
    if (_AI == value) return;
    
    auto oldValue = _AI;
    _AI = value;
    OnChanged(oldValue, value, "AI");
}

void MonsterInfo::SetLevel(int value)
{
    if (_Level == value) return;
    
    auto oldValue = _Level;
    _Level = value;
    OnChanged(oldValue, value, "Level");
}

void MonsterInfo::SetViewRange(int value)
{
    if (_ViewRange == value) return;
    
    auto oldValue = _ViewRange;
    _ViewRange = value;
    OnChanged(oldValue, value, "ViewRange");
}

void MonsterInfo::SetCoolEye(int value)
{
    if (_CoolEye == value) return;
    
    auto oldValue = _CoolEye;
    _CoolEye = value;
    OnChanged(oldValue, value, "CoolEye");
}

void MonsterInfo::SetExperience(decimal value)
{
    if (_Experience == value) return;
    
    auto oldValue = _Experience;
    _Experience = value;
    OnChanged(oldValue, value, "Experience");
}

void MonsterInfo::SetUndead(bool value)
{
    if (_Undead == value) return;
    
    auto oldValue = _Undead;
    _Undead = value;
    OnChanged(oldValue, value, "Undead");
}

void MonsterInfo::SetCanPush(bool value)
{
    if (_CanPush == value) return;
    
    auto oldValue = _CanPush;
    _CanPush = value;
    OnChanged(oldValue, value, "CanPush");
}

void MonsterInfo::SetCanTame(bool value)
{
    if (_CanTame == value) return;
    
    auto oldValue = _CanTame;
    _CanTame = value;
    OnChanged(oldValue, value, "CanTame");
}

void MonsterInfo::SetAttackDelay(int value)
{
    if (_AttackDelay == value) return;
    
    auto oldValue = _AttackDelay;
    _AttackDelay = value;
    OnChanged(oldValue, value, "AttackDelay");
}

void MonsterInfo::SetMoveDelay(int value)
{
    if (_MoveDelay == value) return;
    
    auto oldValue = _MoveDelay;
    _MoveDelay = value;
    OnChanged(oldValue, value, "MoveDelay");
}

void MonsterInfo::SetIsBoss(bool value)
{
    if (_IsBoss == value) return;
    
    auto oldValue = _IsBoss;
    _IsBoss = value;
    OnChanged(oldValue, value, "IsBoss");
}

void MonsterInfo::SetFlag(MonsterFlag value)
{
    if (_Flag == value) return;
    
    auto oldValue = _Flag;
    _Flag = value;
    OnChanged(oldValue, value, "Flag");
}

void MonsterInfo::OnCreated()
{
    DBObject::OnCreated();
    
    CanPush = true;
    ViewRange = 7;
    AttackDelay = 2500;
    MoveDelay = 1800;
}

void MonsterInfo::OnLoaded()
{
    DBObject::OnLoaded();
    StatsChanged();
}

void MonsterInfo::StatsChanged()
{
    Stats.Clear();
    for (auto* stat : MonsterInfoStats)
        Stats[stat->Stat] += stat->Amount;
}

}} // namespace Library::SystemModels
