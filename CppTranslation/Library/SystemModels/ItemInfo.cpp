#include "ItemInfo.h"
#include "../MirDB/DBBindingList.h"

namespace Library { namespace SystemModels {

void ItemInfo::SetItemName(const std::string& value)
{
    if (_ItemName == value) return;
    
    auto oldValue = _ItemName;
    _ItemName = value;
    OnChanged(oldValue, value, "ItemName");
}

void ItemInfo::SetItemType(ItemType value)
{
    if (_ItemType == value) return;
    
    auto oldValue = _ItemType;
    _ItemType = value;
    OnChanged(oldValue, value, "ItemType");
}

void ItemInfo::SetRequiredClass(RequiredClass value)
{
    if (_RequiredClass == value) return;
    
    auto oldValue = _RequiredClass;
    _RequiredClass = value;
    OnChanged(oldValue, value, "RequiredClass");
}

void ItemInfo::SetRequiredGender(RequiredGender value)
{
    if (_RequiredGender == value) return;
    
    auto oldValue = _RequiredGender;
    _RequiredGender = value;
    OnChanged(oldValue, value, "RequiredGender");
}

void ItemInfo::SetRequiredType(RequiredType value)
{
    if (_RequiredType == value) return;
    
    auto oldValue = _RequiredType;
    _RequiredType = value;
    OnChanged(oldValue, value, "RequiredType");
}

void ItemInfo::SetRequiredAmount(int value)
{
    if (_RequiredAmount == value) return;
    
    auto oldValue = _RequiredAmount;
    _RequiredAmount = value;
    OnChanged(oldValue, value, "RequiredAmount");
}

void ItemInfo::SetShape(int value)
{
    if (_Shape == value) return;
    
    auto oldValue = _Shape;
    _Shape = value;
    OnChanged(oldValue, value, "Shape");
}

void ItemInfo::SetEffect(ItemEffect value)
{
    if (_Effect == value) return;
    
    auto oldValue = _Effect;
    _Effect = value;
    OnChanged(oldValue, value, "Effect");
}

void ItemInfo::SetImage(int value)
{
    if (_Image == value) return;
    
    auto oldValue = _Image;
    _Image = value;
    OnChanged(oldValue, value, "Image");
}

void ItemInfo::SetDurability(int value)
{
    if (_Durability == value) return;
    
    auto oldValue = _Durability;
    _Durability = value;
    OnChanged(oldValue, value, "Durability");
}

void ItemInfo::SetPrice(int value)
{
    if (_Price == value) return;
    
    auto oldValue = _Price;
    _Price = value;
    OnChanged(oldValue, value, "Price");
}

void ItemInfo::SetWeight(int value)
{
    if (_Weight == value) return;
    
    auto oldValue = _Weight;
    _Weight = value;
    OnChanged(oldValue, value, "Weight");
}

void ItemInfo::SetStackSize(int value)
{
    if (_StackSize == value) return;
    
    auto oldValue = _StackSize;
    _StackSize = value;
    OnChanged(oldValue, value, "StackSize");
}

void ItemInfo::SetStartItem(bool value)
{
    if (_StartItem == value) return;
    
    auto oldValue = _StartItem;
    _StartItem = value;
    OnChanged(oldValue, value, "StartItem");
}

void ItemInfo::SetSellRate(decimal value)
{
    if (_SellRate == value) return;
    
    auto oldValue = _SellRate;
    _SellRate = value;
    OnChanged(oldValue, value, "SellRate");
}

void ItemInfo::SetCanRepair(bool value)
{
    if (_CanRepair == value) return;
    
    auto oldValue = _CanRepair;
    _CanRepair = value;
    OnChanged(oldValue, value, "CanRepair");
}

void ItemInfo::SetCanSell(bool value)
{
    if (_CanSell == value) return;
    
    auto oldValue = _CanSell;
    _CanSell = value;
    OnChanged(oldValue, value, "CanSell");
}

void ItemInfo::SetCanStore(bool value)
{
    if (_CanStore == value) return;
    
    auto oldValue = _CanStore;
    _CanStore = value;
    OnChanged(oldValue, value, "CanStore");
}

void ItemInfo::SetCanTrade(bool value)
{
    if (_CanTrade == value) return;
    
    auto oldValue = _CanTrade;
    _CanTrade = value;
    OnChanged(oldValue, value, "CanTrade");
}

void ItemInfo::SetCanDrop(bool value)
{
    if (_CanDrop == value) return;
    
    auto oldValue = _CanDrop;
    _CanDrop = value;
    OnChanged(oldValue, value, "CanDrop");
}

void ItemInfo::SetCanDeathDrop(bool value)
{
    if (_CanDeathDrop == value) return;
    
    auto oldValue = _CanDeathDrop;
    _CanDeathDrop = value;
    OnChanged(oldValue, value, "CanDeathDrop");
}

void ItemInfo::SetDescription(const std::string& value)
{
    if (_Description == value) return;
    
    auto oldValue = _Description;
    _Description = value;
    OnChanged(oldValue, value, "Description");
}

void ItemInfo::SetRarity(Rarity value)
{
    if (_Rarity == value) return;
    
    auto oldValue = _Rarity;
    _Rarity = value;
    OnChanged(oldValue, value, "Rarity");
}

void ItemInfo::SetCanAutoPot(bool value)
{
    if (_CanAutoPot == value) return;
    
    auto oldValue = _CanAutoPot;
    _CanAutoPot = value;
    OnChanged(oldValue, value, "CanAutoPot");
}

void ItemInfo::SetBuffIcon(int value)
{
    if (_BuffIcon == value) return;
    
    auto oldValue = _BuffIcon;
    _BuffIcon = value;
    OnChanged(oldValue, value, "BuffIcon");
}

void ItemInfo::SetPartCount(int value)
{
    if (_PartCount == value) return;
    
    auto oldValue = _PartCount;
    _PartCount = value;
    OnChanged(oldValue, value, "PartCount");
}

void ItemInfo::SetSet(SetInfo* value)
{
    if (_Set == value) return;
    
    auto oldValue = _Set;
    _Set = value;
    OnChanged(oldValue, value, "Set");
}

void ItemInfo::OnCreated()
{
    DBObject::OnCreated();
    
    StackSize = 1;
    RequiredGender = RequiredGender::None;
    RequiredClass = RequiredClass::All;
    SellRate = 0.5M;
    CanRepair = true;
    CanSell = true;
    CanStore = true;
    CanTrade = true;
    CanDrop = true;
}

void ItemInfo::OnLoaded()
{
    DBObject::OnLoaded();
    StatsChanged();
}

void ItemInfo::StatsChanged()
{
    Stats.Clear();
    for (auto* stat : ItemStats)
        Stats[stat->Stat] += stat->Amount;
}

std::string ItemInfo::ToString() const
{
    return _ItemName;
}

}} // namespace Library::SystemModels
