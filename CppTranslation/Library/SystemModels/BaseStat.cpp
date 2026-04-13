#include "BaseStat.h"

namespace Library::SystemModels
{
    void BaseStat::SetClass(MirClass value)
    {
        if (_Class == value) return;
        
        MirClass oldValue = _Class;
        _Class = value;
        
        OnChanged(oldValue, value, "Class");
    }

    void BaseStat::SetLevel(int value)
    {
        if (_Level == value) return;
        
        int oldValue = _Level;
        _Level = value;
        
        OnChanged(oldValue, value, "Level");
    }

    void BaseStat::SetHealth(int value)
    {
        if (_Health == value) return;
        
        int oldValue = _Health;
        _Health = value;
        
        OnChanged(oldValue, value, "Health");
    }

    void BaseStat::SetMana(int value)
    {
        if (_Mana == value) return;
        
        int oldValue = _Mana;
        _Mana = value;
        
        OnChanged(oldValue, value, "Mana");
    }

    void BaseStat::SetBagWeight(int value)
    {
        if (_BagWeight == value) return;
        
        int oldValue = _BagWeight;
        _BagWeight = value;
        
        OnChanged(oldValue, value, "BagWeight");
    }

    void BaseStat::SetWearWeight(int value)
    {
        if (_WearWeight == value) return;
        
        int oldValue = _WearWeight;
        _WearWeight = value;
        
        OnChanged(oldValue, value, "WearWeight");
    }

    void BaseStat::SetHandWeight(int value)
    {
        if (_HandWeight == value) return;
        
        int oldValue = _HandWeight;
        _HandWeight = value;
        
        OnChanged(oldValue, value, "HandWeight");
    }

    void BaseStat::SetAccuracy(int value)
    {
        if (_Accuracy == value) return;
        
        int oldValue = _Accuracy;
        _Accuracy = value;
        
        OnChanged(oldValue, value, "Accuracy");
    }

    void BaseStat::SetAgility(int value)
    {
        if (_Agility == value) return;
        
        int oldValue = _Agility;
        _Agility = value;
        
        OnChanged(oldValue, value, "Agility");
    }

    void BaseStat::SetMinAC(int value)
    {
        if (_MinAC == value) return;
        
        int oldValue = _MinAC;
        _MinAC = value;
        
        OnChanged(oldValue, value, "MinAC");
    }

    void BaseStat::SetMaxAC(int value)
    {
        if (_MaxAC == value) return;
        
        int oldValue = _MaxAC;
        _MaxAC = value;
        
        OnChanged(oldValue, value, "MaxAC");
    }

    void BaseStat::SetMinMR(int value)
    {
        if (_MinMR == value) return;
        
        int oldValue = _MinMR;
        _MinMR = value;
        
        OnChanged(oldValue, value, "MinMR");
    }

    void BaseStat::SetMaxMR(int value)
    {
        if (_MaxMR == value) return;
        
        int oldValue = _MaxMR;
        _MaxMR = value;
        
        OnChanged(oldValue, value, "MaxMR");
    }

    void BaseStat::SetMinDC(int value)
    {
        if (_MinDC == value) return;
        
        int oldValue = _MinDC;
        _MinDC = value;
        
        OnChanged(oldValue, value, "MinDC");
    }

    void BaseStat::SetMaxDC(int value)
    {
        if (_MaxDC == value) return;
        
        int oldValue = _MaxDC;
        _MaxDC = value;
        
        OnChanged(oldValue, value, "MaxDC");
    }

    void BaseStat::SetMinMC(int value)
    {
        if (_MinMC == value) return;
        
        int oldValue = _MinMC;
        _MinMC = value;
        
        OnChanged(oldValue, value, "MinMC");
    }

    void BaseStat::SetMaxMC(int value)
    {
        if (_MaxMC == value) return;
        
        int oldValue = _MaxMC;
        _MaxMC = value;
        
        OnChanged(oldValue, value, "MaxMC");
    }

    void BaseStat::SetMinSC(int value)
    {
        if (_MinSC == value) return;
        
        int oldValue = _MinSC;
        _MinSC = value;
        
        OnChanged(oldValue, value, "MinSC");
    }

    void BaseStat::SetMaxSC(int value)
    {
        if (_MaxSC == value) return;
        
        int oldValue = _MaxSC;
        _MaxSC = value;
        
        OnChanged(oldValue, value, "MaxSC");
    }

} // namespace Library::SystemModels
