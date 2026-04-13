#include "MagicInfo.h"

namespace Server::DBModels
{
    void MagicInfo::SetName(const std::string& value)
    {
        if (_Name == value) return;
        std::string oldValue = _Name;
        _Name = value;
        OnChanged(oldValue, value, "Name");
    }

    void MagicInfo::SetMagic(Library::MagicType value)
    {
        if (_Magic == value) return;
        Library::MagicType oldValue = _Magic;
        _Magic = value;
        OnChanged(oldValue, value, "Magic");
    }

    void MagicInfo::SetClass(Library::MirClass value)
    {
        if (_Class == value) return;
        Library::MirClass oldValue = _Class;
        _Class = value;
        OnChanged(oldValue, value, "Class");
    }

    void MagicInfo::SetSchool(Library::MagicSchool value)
    {
        if (_School == value) return;
        Library::MagicSchool oldValue = _School;
        _School = value;
        OnChanged(oldValue, value, "School");
    }

    void MagicInfo::SetIcon(int value)
    {
        if (_Icon == value) return;
        int oldValue = _Icon;
        _Icon = value;
        OnChanged(oldValue, value, "Icon");
    }

    void MagicInfo::SetRequiredLevel(int value)
    {
        if (_RequiredLevel == value) return;
        int oldValue = _RequiredLevel;
        _RequiredLevel = value;
        OnChanged(oldValue, value, "RequiredLevel");
    }

    void MagicInfo::SetMinBasePower(int value)
    {
        if (_MinBasePower == value) return;
        int oldValue = _MinBasePower;
        _MinBasePower = value;
        OnChanged(oldValue, value, "MinBasePower");
    }

    void MagicInfo::SetMaxBasePower(int value)
    {
        if (_MaxBasePower == value) return;
        int oldValue = _MaxBasePower;
        _MaxBasePower = value;
        OnChanged(oldValue, value, "MaxBasePower");
    }

    void MagicInfo::SetMinLevelPower(int value)
    {
        if (_MinLevelPower == value) return;
        int oldValue = _MinLevelPower;
        _MinLevelPower = value;
        OnChanged(oldValue, value, "MinLevelPower");
    }

    void MagicInfo::SetMaxLevelPower(int value)
    {
        if (_MaxLevelPower == value) return;
        int oldValue = _MaxLevelPower;
        _MaxLevelPower = value;
        OnChanged(oldValue, value, "MaxLevelPower");
    }

    void MagicInfo::SetBaseCost(int value)
    {
        if (_BaseCost == value) return;
        int oldValue = _BaseCost;
        _BaseCost = value;
        OnChanged(oldValue, value, "BaseCost");
    }

    void MagicInfo::SetLevelCost(int value)
    {
        if (_LevelCost == value) return;
        int oldValue = _LevelCost;
        _LevelCost = value;
        OnChanged(oldValue, value, "LevelCost");
    }

    void MagicInfo::SetBaseExperience(int value)
    {
        if (_BaseExperience == value) return;
        int oldValue = _BaseExperience;
        _BaseExperience = value;
        OnChanged(oldValue, value, "BaseExperience");
    }

    void MagicInfo::SetExperienceRate(int value)
    {
        if (_ExperienceRate == value) return;
        int oldValue = _ExperienceRate;
        _ExperienceRate = value;
        OnChanged(oldValue, value, "ExperienceRate");
    }

    void MagicInfo::SetMaxLevel(int value)
    {
        if (_MaxLevel == value) return;
        int oldValue = _MaxLevel;
        _MaxLevel = value;
        OnChanged(oldValue, value, "MaxLevel");
    }

    void MagicInfo::SetDelay(int value)
    {
        if (_Delay == value) return;
        int oldValue = _Delay;
        _Delay = value;
        OnChanged(oldValue, value, "Delay");
    }

    void MagicInfo::OnCreated()
    {
        DBObject::OnCreated();
        SetExperienceRate(5);
    }

    ClientMagicInfo MagicInfo::ToClientInfo()
    {
        ClientMagicInfo info{};
        info.Index = GetIndex();
        info.Name = GetName();
        info.Magic = GetMagic();
        info.Class = GetClass();
        info.School = GetSchool();
        info.Icon = GetIcon();
        info.RequiredLevel = GetRequiredLevel();
        info.MinBasePower = GetMinBasePower();
        info.MaxBasePower = GetMaxBasePower();
        info.MinLevelPower = GetMinLevelPower();
        info.MaxLevelPower = GetMaxLevelPower();
        info.BaseCost = GetBaseCost();
        info.LevelCost = GetLevelCost();
        info.BaseExperience = GetBaseExperience();
        info.ExperienceRate = GetExperienceRate();
        info.Delay = GetDelay();
        return info;
    }
} // namespace Server::DBModels
