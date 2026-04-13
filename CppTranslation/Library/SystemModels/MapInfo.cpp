#include "MapInfo.h"

namespace Library { namespace SystemModels {

void MapInfo::SetFileName(const std::string& value)
{
    if (_FileName == value) return;
    
    auto oldValue = _FileName;
    _FileName = value;
    OnChanged(oldValue, value, "FileName");
}

void MapInfo::SetDescription(const std::string& value)
{
    if (_Description == value) return;
    
    auto oldValue = _Description;
    _Description = value;
    OnChanged(oldValue, value, "Description");
}

void MapInfo::SetMiniMap(int value)
{
    if (_MiniMap == value) return;
    
    auto oldValue = _MiniMap;
    _MiniMap = value;
    OnChanged(oldValue, value, "MiniMap");
}

void MapInfo::SetLight(LightSetting value)
{
    if (_Light == value) return;
    
    auto oldValue = _Light;
    _Light = value;
    OnChanged(oldValue, value, "Light");
}

void MapInfo::SetFight(FightSetting value)
{
    if (_Fight == value) return;
    
    auto oldValue = _Fight;
    _Fight = value;
    OnChanged(oldValue, value, "Fight");
}

void MapInfo::SetAllowRT(bool value)
{
    if (_AllowRT == value) return;
    
    auto oldValue = _AllowRT;
    _AllowRT = value;
    OnChanged(oldValue, value, "AllowRT");
}

void MapInfo::SetSkillDelay(int value)
{
    if (_SkillDelay == value) return;
    
    auto oldValue = _SkillDelay;
    _SkillDelay = value;
    OnChanged(oldValue, value, "SkillDelay");
}

void MapInfo::SetCanHorse(bool value)
{
    if (_CanHorse == value) return;
    
    auto oldValue = _CanHorse;
    _CanHorse = value;
    OnChanged(oldValue, value, "CanHorse");
}

void MapInfo::SetAllowTT(bool value)
{
    if (_AllowTT == value) return;
    
    auto oldValue = _AllowTT;
    _AllowTT = value;
    OnChanged(oldValue, value, "AllowTT");
}

void MapInfo::SetCanMine(bool value)
{
    if (_CanMine == value) return;
    
    auto oldValue = _CanMine;
    _CanMine = value;
    OnChanged(oldValue, value, "CanMine");
}

void MapInfo::SetCanMarriageRecall(bool value)
{
    if (_CanMarriageRecall == value) return;
    
    auto oldValue = _CanMarriageRecall;
    _CanMarriageRecall = value;
    OnChanged(oldValue, value, "CanMarriageRecall");
}

void MapInfo::SetAllowRecall(bool value)
{
    if (_AllowRecall == value) return;
    
    auto oldValue = _AllowRecall;
    _AllowRecall = value;
    OnChanged(oldValue, value, "AllowRecall");
}

void MapInfo::SetMinimumLevel(int value)
{
    if (_MinimumLevel == value) return;
    
    auto oldValue = _MinimumLevel;
    _MinimumLevel = value;
    OnChanged(oldValue, value, "MinimumLevel");
}

void MapInfo::SetMaximumLevel(int value)
{
    if (_MaximumLevel == value) return;
    
    auto oldValue = _MaximumLevel;
    _MaximumLevel = value;
    OnChanged(oldValue, value, "MaximumLevel");
}

void MapInfo::SetReconnectMap(MapInfo* value)
{
    if (_ReconnectMap == value) return;
    
    auto oldValue = _ReconnectMap;
    _ReconnectMap = value;
    OnChanged(oldValue, value, "ReconnectMap");
}

void MapInfo::SetMusic(SoundIndex value)
{
    if (_Music == value) return;
    
    auto oldValue = _Music;
    _Music = value;
    OnChanged(oldValue, value, "Music");
}

void MapInfo::SetMonsterHealth(int value)
{
    if (_MonsterHealth == value) return;
    
    auto oldValue = _MonsterHealth;
    _MonsterHealth = value;
    OnChanged(oldValue, value, "MonsterHealth");
}

void MapInfo::SetMonsterDamage(int value)
{
    if (_MonsterDamage == value) return;
    
    auto oldValue = _MonsterDamage;
    _MonsterDamage = value;
    OnChanged(oldValue, value, "MonsterDamage");
}

void MapInfo::SetDropRate(int value)
{
    if (_DropRate == value) return;
    
    auto oldValue = _DropRate;
    _DropRate = value;
    OnChanged(oldValue, value, "DropRate");
}

void MapInfo::SetExperienceRate(int value)
{
    if (_ExperienceRate == value) return;
    
    auto oldValue = _ExperienceRate;
    _ExperienceRate = value;
    OnChanged(oldValue, value, "ExperienceRate");
}

void MapInfo::SetGoldRate(int value)
{
    if (_GoldRate == value) return;
    
    auto oldValue = _GoldRate;
    _GoldRate = value;
    OnChanged(oldValue, value, "GoldRate");
}

void MapInfo::SetMaxMonsterHealth(int value)
{
    if (_MaxMonsterHealth == value) return;
    
    auto oldValue = _MaxMonsterHealth;
    _MaxMonsterHealth = value;
    OnChanged(oldValue, value, "MaxMonsterHealth");
}

void MapInfo::SetMaxMonsterDamage(int value)
{
    if (_MaxMonsterDamage == value) return;
    
    auto oldValue = _MaxMonsterDamage;
    _MaxMonsterDamage = value;
    OnChanged(oldValue, value, "MaxMonsterDamage");
}

void MapInfo::SetMaxDropRate(int value)
{
    if (_MaxDropRate == value) return;
    
    auto oldValue = _MaxDropRate;
    _MaxDropRate = value;
    OnChanged(oldValue, value, "MaxDropRate");
}

void MapInfo::SetMaxExperienceRate(int value)
{
    if (_MaxExperienceRate == value) return;
    
    auto oldValue = _MaxExperienceRate;
    _MaxExperienceRate = value;
    OnChanged(oldValue, value, "MaxExperienceRate");
}

void MapInfo::SetMaxGoldRate(int value)
{
    if (_MaxGoldRate == value) return;
    
    auto oldValue = _MaxGoldRate;
    _MaxGoldRate = value;
    OnChanged(oldValue, value, "MaxGoldRate");
}

void MapInfo::OnCreated()
{
    DBObject::OnCreated();
    
    AllowRT = true;
    AllowTT = true;
    CanMarriageRecall = true;
    AllowRecall = true;
}

}} // namespace Library::SystemModels
