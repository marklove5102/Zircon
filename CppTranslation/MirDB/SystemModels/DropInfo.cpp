#include "DropInfo.h"
#include "MonsterInfo.h"
#include "ItemInfo.h"

namespace Server::DBModels
{
    void DropInfo::SetMonster(MonsterInfo* value)
    {
        if (_Monster == value) return;

        MonsterInfo* oldValue = _Monster;
        _Monster = value;

        OnChanged(oldValue, value, "Monster");
    }

    void DropInfo::SetItem(ItemInfo* value)
    {
        if (_Item == value) return;

        ItemInfo* oldValue = _Item;
        _Item = value;

        OnChanged(oldValue, value, "Item");
    }

    void DropInfo::SetChance(int value)
    {
        if (_Chance == value) return;

        int oldValue = _Chance;
        _Chance = value;

        OnChanged(oldValue, value, "Chance");
    }

    void DropInfo::SetAmount(int value)
    {
        if (_Amount == value) return;

        int oldValue = _Amount;
        _Amount = value;

        OnChanged(oldValue, value, "Amount");
    }

    void DropInfo::SetDropSet(int value)
    {
        if (_DropSet == value) return;

        int oldValue = _DropSet;
        _DropSet = value;

        OnChanged(oldValue, value, "DropSet");
    }

    void DropInfo::OnCreated()
    {
        DBObject::OnCreated();

        SetAmount(1);
    }

} // namespace Server::DBModels
