#include "MagicInfo.h"

namespace Library { namespace SystemModels {

void MagicInfo::SetName(const std::string& value)
{
    if (_Name == value) return;
    
    auto oldValue = _Name;
    _Name = value;
    OnChanged(oldValue, value, "Name");
}

void MagicInfo::SetMagic(MagicType value)
{
    if (_Magic == value) return;
    
    auto oldValue = _Magic;
    _Magic = value;
    OnChanged(oldValue, value, "Magic");
}

void MagicInfo::SetClass(MirClass value)
{
    if (_Class == value) return;
    
    auto oldValue = _Class;
    _Class = value;
    OnChanged(oldValue, value, "Class");
}

void MagicInfo::SetSchool(MagicSchool value)
{
    if (_School == value) return;
    
    auto oldValue = _School;
    _School = value;
    OnChanged(oldValue, value, "School");
}

void MagicInfo::SetIcon(int value)
{
    if (_Icon == value) return;
    
    auto oldValue = _Icon;
    _Icon = value;
    OnChanged(oldValue, value, "Icon");
}

void MagicInfo::SetMinBasePower(int value)
{
    if (_MinBasePower == value) return;
    
    auto oldValue = _MinBasePower;
    _MinBasePower = value;
    OnChanged(oldValue, value, "MinBasePower");
}

void MagicInfo::SetMaxBasePower(int value)
{
    if (_MaxBasePower == value) return;
    
    auto oldValue = _MaxBasePower;
    _MaxBasePower = value;
    OnChanged(oldValue, value, "MaxBasePower");
}

void MagicInfo::SetMinLevelPower(int value)
{
    if (_MinLevelPower == value) return;
    
    auto oldValue = _MinLevelPower;
    _MinLevelPower = value;
    OnChanged(oldValue, value, "MinLevelPower");
}

void MagicInfo::SetMaxLevelPower(int value)
{
    if (_MaxLevelPower == value) return;
    
    auto oldValue = _MaxLevelPower;
    _MaxLevelPower = value;
    OnChanged(oldValue, value, "MaxLevelPower");
}

void MagicInfo::SetBaseCost(int value)
{
    if (_BaseCost == value) return;
    
    auto oldValue = _BaseCost;
    _BaseCost = value;
    OnChanged(oldValue, value, "BaseCost");
}

void MagicInfo::SetLevelCost(int value)
{
    if (_LevelCost == value) return;
    
    auto oldValue = _LevelCost;
    _LevelCost = value;
    OnChanged(oldValue, value, "LevelCost");
}

void MagicInfo::SetNeedLevel1(int value)
{
    if (_NeedLevel1 == value) return;
    
    auto oldValue = _NeedLevel1;
    _NeedLevel1 = value;
    OnChanged(oldValue, value, "NeedLevel1");
}

void MagicInfo::SetNeedLevel2(int value)
{
    if (_NeedLevel2 == value) return;
    
    auto oldValue = _NeedLevel2;
    _NeedLevel2 = value;
    OnChanged(oldValue, value, "NeedLevel2");
}

void MagicInfo::SetNeedLevel3(int value)
{
    if (_NeedLevel3 == value) return;
    
    auto oldValue = _NeedLevel3;
    _NeedLevel3 = value;
    OnChanged(oldValue, value, "NeedLevel3");
}

void MagicInfo::SetExperience1(int value)
{
    if (_Experience1 == value) return;
    
    auto oldValue = _Experience1;
    _Experience1 = value;
    OnChanged(oldValue, value, "Experience1");
}

void MagicInfo::SetExperience2(int value)
{
    if (_Experience2 == value) return;
    
    auto oldValue = _Experience2;
    _Experience2 = value;
    OnChanged(oldValue, value, "Experience2");
}

void MagicInfo::SetExperience3(int value)
{
    if (_Experience3 == value) return;
    
    auto oldValue = _Experience3;
    _Experience3 = value;
    OnChanged(oldValue, value, "Experience3");
}

void MagicInfo::SetDelay(int value)
{
    if (_Delay == value) return;
    
    auto oldValue = _Delay;
    _Delay = value;
    OnChanged(oldValue, value, "Delay");
}

void MagicInfo::SetDescription(const std::string& value)
{
    if (_Description == value) return;
    
    auto oldValue = _Description;
    _Description = value;
    OnChanged(oldValue, value, "Description");
}

}} // namespace Library::SystemModels
