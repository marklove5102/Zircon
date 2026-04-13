#include "ItemInfoStat.h"
#include "ItemInfo.h"

namespace Server::DBModels
{
    void ItemInfoStat::SetItem(ItemInfo* value)
    {
        if (_Item == value) return;
        ItemInfo* oldValue = _Item;
        _Item = value;
        OnChanged(oldValue, value, "Item");
    }

    void ItemInfoStat::SetStat(Library::Stat value)
    {
        if (_Stat == value) return;
        Library::Stat oldValue = _Stat;
        _Stat = value;
        OnChanged(oldValue, value, "Stat");
    }

    void ItemInfoStat::SetAmount(int value)
    {
        if (_Amount == value) return;
        int oldValue = _Amount;
        _Amount = value;
        OnChanged(oldValue, value, "Amount");
    }
} // namespace Server::DBModels
