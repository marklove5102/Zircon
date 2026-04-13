#include "SetInfoStat.h"
#include "SetInfo.h"

namespace Server::DBModels
{
    void SetInfoStats::SetSet(SetInfo* value)
    {
        if (_Set == value) return;

        auto oldValue = _Set;
        _Set = value;

        OnChanged(oldValue, value, "Set");
    }

    void SetInfoStats::SetStat(Stat value)
    {
        if (_Stat == value) return;

        auto oldValue = _Stat;
        _Stat = value;

        OnChanged(oldValue, value, "Stat");
    }

    void SetInfoStats::SetAmount(int value)
    {
        if (_Amount == value) return;

        auto oldValue = _Amount;
        _Amount = value;

        OnChanged(oldValue, value, "Amount");
    }

    void SetInfoStats::SetClass(RequiredClass value)
    {
        if (_Class == value) return;

        auto oldValue = _Class;
        _Class = value;

        OnChanged(oldValue, value, "Class");
    }

    void SetInfoStats::SetLevel(int value)
    {
        if (_Level == value) return;

        auto oldValue = _Level;
        _Level = value;

        OnChanged(oldValue, value, "Level");
    }

    void SetInfoStats::OnCreated()
    {
        DBObject::OnCreated();
        _Class = RequiredClass::All;
    }
}
