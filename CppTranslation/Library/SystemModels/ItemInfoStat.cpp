#include "ItemInfoStat.h"
#include "ItemInfo.h"

namespace Library { namespace SystemModels {

void ItemInfoStat::SetItem(ItemInfo* value)
{
    if (_Item == value) return;
    
    auto oldValue = _Item;
    _Item = value;
    OnChanged(oldValue, value, "Item");
}

void ItemInfoStat::SetStat(Stat value)
{
    if (_Stat == value) return;
    
    auto oldValue = _Stat;
    _Stat = value;
    OnChanged(oldValue, value, "Stat");
}

void ItemInfoStat::SetAmount(int value)
{
    if (_Amount == value) return;
    
    auto oldValue = _Amount;
    _Amount = value;
    OnChanged(oldValue, value, "Amount");
}

}} // namespace Library::SystemModels
