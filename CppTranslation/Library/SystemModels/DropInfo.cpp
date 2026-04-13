#include "DropInfo.h"
#include "MonsterInfo.h"
#include "ItemInfo.h"

namespace Library { namespace SystemModels {

void DropInfo::SetMonster(MonsterInfo* value)
{
    if (_Monster == value) return;
    
    auto oldValue = _Monster;
    _Monster = value;
    OnChanged(oldValue, value, "Monster");
}

void DropInfo::SetItem(ItemInfo* value)
{
    if (_Item == value) return;
    
    auto oldValue = _Item;
    _Item = value;
    OnChanged(oldValue, value, "Item");
}

void DropInfo::SetChance(int value)
{
    if (_Chance == value) return;
    
    auto oldValue = _Chance;
    _Chance = value;
    OnChanged(oldValue, value, "Chance");
}

void DropInfo::SetAmount(int value)
{
    if (_Amount == value) return;
    
    auto oldValue = _Amount;
    _Amount = value;
    OnChanged(oldValue, value, "Amount");
}

void DropInfo::SetDropSet(int value)
{
    if (_DropSet == value) return;
    
    auto oldValue = _DropSet;
    _DropSet = value;
    OnChanged(oldValue, value, "DropSet");
}

void DropInfo::SetPartOnly(bool value)
{
    if (_PartOnly == value) return;
    
    auto oldValue = _PartOnly;
    _PartOnly = value;
    OnChanged(oldValue, value, "PartOnly");
}

void DropInfo::SetEasterEvent(bool value)
{
    if (_EasterEvent == value) return;
    
    auto oldValue = _EasterEvent;
    _EasterEvent = value;
    OnChanged(oldValue, value, "EasterEvent");
}

void DropInfo::OnCreated()
{
    DBObject::OnCreated();
    Amount = 1;
}

}} // namespace Library::SystemModels
