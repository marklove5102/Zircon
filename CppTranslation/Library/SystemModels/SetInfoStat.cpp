#include "SetInfoStat.h"
#include "SetInfo.h"

namespace Library { namespace SystemModels {

void SetInfoStat::SetSet(SetInfo* value)
{
    if (_Set == value) return;
    
    auto oldValue = _Set;
    _Set = value;
    OnChanged(oldValue, value, "Set");
}

void SetInfoStat::SetStat(Stat value)
{
    if (_Stat == value) return;
    
    auto oldValue = _Stat;
    _Stat = value;
    OnChanged(oldValue, value, "Stat");
}

void SetInfoStat::SetAmount(int value)
{
    if (_Amount == value) return;
    
    auto oldValue = _Amount;
    _Amount = value;
    OnChanged(oldValue, value, "Amount");
}

void SetInfoStat::SetClass(RequiredClass value)
{
    if (_Class == value) return;
    
    auto oldValue = _Class;
    _Class = value;
    OnChanged(oldValue, value, "Class");
}

void SetInfoStat::SetLevel(int value)
{
    if (_Level == value) return;
    
    auto oldValue = _Level;
    _Level = value;
    OnChanged(oldValue, value, "Level");
}

void SetInfoStat::OnCreated()
{
    DBObject::OnCreated();
    Class = RequiredClass::All;
}

}} // namespace Library::SystemModels
