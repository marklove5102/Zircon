#include "ItemInfo.h"
#include "SetInfo.h"
#include "ItemInfoStat.h"
#include "DropInfo.h"

namespace Server::DBModels
{
    void ItemInfo::SetItemName(const std::string& value)
    {
        if (_ItemName == value) return;
        std::string oldValue = _ItemName;
        _ItemName = value;
        OnChanged(oldValue, value, "ItemName");
    }

    void ItemInfo::SetItemType(Library::ItemType value)
    {
        if (_ItemType == value) return;
        Library::ItemType oldValue = _ItemType;
        _ItemType = value;
        OnChanged(oldValue, value, "ItemType");
    }

    void ItemInfo::SetRequiredClass(Library::RequiredClass value)
    {
        if (_RequiredClass == value) return;
        Library::RequiredClass oldValue = _RequiredClass;
        _RequiredClass = value;
        OnChanged(oldValue, value, "RequiredClass");
    }

    void ItemInfo::SetRequiredGender(Library::RequiredGender value)
    {
        if (_RequiredGender == value) return;
        Library::RequiredGender oldValue = _RequiredGender;
        _RequiredGender = value;
        OnChanged(oldValue, value, "RequiredGender");
    }

    void ItemInfo::SetRequiredType(Library::RequiredType value)
    {
        if (_RequiredType == value) return;
        Library::RequiredType oldValue = _RequiredType;
        _RequiredType = value;
        OnChanged(oldValue, value, "RequiredType");
    }

    void ItemInfo::SetRequiredAmount(int value)
    {
        if (_RequiredAmount == value) return;
        int oldValue = _RequiredAmount;
        _RequiredAmount = value;
        OnChanged(oldValue, value, "RequiredAmount");
    }

    void ItemInfo::SetShape(int value)
    {
        if (_Shape == value) return;
        int oldValue = _Shape;
        _Shape = value;
        OnChanged(oldValue, value, "Shape");
    }

    void ItemInfo::SetEffect(Library::ItemEffect value)
    {
        if (_Effect == value) return;
        Library::ItemEffect oldValue = _Effect;
        _Effect = value;
        OnChanged(oldValue, value, "Effect");
    }

    void ItemInfo::SetImage(int value)
    {
        if (_Image == value) return;
        int oldValue = _Image;
        _Image = value;
        OnChanged(oldValue, value, "Image");
    }

    void ItemInfo::SetDurability(int value)
    {
        if (_Durability == value) return;
        int oldValue = _Durability;
        _Durability = value;
        OnChanged(oldValue, value, "Durability");
    }

    void ItemInfo::SetPrice(int value)
    {
        if (_Price == value) return;
        int oldValue = _Price;
        _Price = value;
        OnChanged(oldValue, value, "Price");
    }

    void ItemInfo::SetStackSize(int value)
    {
        if (_StackSize == value) return;
        int oldValue = _StackSize;
        _StackSize = value;
        OnChanged(oldValue, value, "StackSize");
    }

    void ItemInfo::SetStartItem(bool value)
    {
        if (_StartItem == value) return;
        bool oldValue = _StartItem;
        _StartItem = value;
        OnChanged(oldValue, value, "StartItem");
    }

    void ItemInfo::SetSellRate(double value)
    {
        if (_SellRate == value) return;
        double oldValue = _SellRate;
        _SellRate = value;
        OnChanged(oldValue, value, "SellRate");
    }

    void ItemInfo::SetCanRepair(bool value)
    {
        if (_CanRepair == value) return;
        bool oldValue = _CanRepair;
        _CanRepair = value;
        OnChanged(oldValue, value, "CanRepair");
    }

    void ItemInfo::SetCanSell(bool value)
    {
        if (_CanSell == value) return;
        bool oldValue = _CanSell;
        _CanSell = value;
        OnChanged(oldValue, value, "CanSell");
    }

    void ItemInfo::SetCanStore(bool value)
    {
        if (_CanStore == value) return;
        bool oldValue = _CanStore;
        _CanStore = value;
        OnChanged(oldValue, value, "CanStore");
    }

    void ItemInfo::SetCanTrade(bool value)
    {
        if (_CanTrade == value) return;
        bool oldValue = _CanTrade;
        _CanTrade = value;
        OnChanged(oldValue, value, "CanTrade");
    }

    void ItemInfo::SetCanDrop(bool value)
    {
        if (_CanDrop == value) return;
        bool oldValue = _CanDrop;
        _CanDrop = value;
        OnChanged(oldValue, value, "CanDrop");
    }

    void ItemInfo::SetCanDeathDrop(bool value)
    {
        if (_CanDeathDrop == value) return;
        bool oldValue = _CanDeathDrop;
        _CanDeathDrop = value;
        OnChanged(oldValue, value, "CanDeathDrop");
    }

    void ItemInfo::SetDescription(const std::string& value)
    {
        if (_Description == value) return;
        std::string oldValue = _Description;
        _Description = value;
        OnChanged(oldValue, value, "Description");
    }

    void ItemInfo::SetRarity(Library::Rarity value)
    {
        if (_Rarity == value) return;
        Library::Rarity oldValue = _Rarity;
        _Rarity = value;
        OnChanged(oldValue, value, "Rarity");
    }

    void ItemInfo::SetCanAutoPot(bool value)
    {
        if (_CanAutoPot == value) return;
        bool oldValue = _CanAutoPot;
        _CanAutoPot = value;
        OnChanged(oldValue, value, "CanAutoPot");
    }

    void ItemInfo::SetSet(SetInfo* value)
    {
        if (_Set == value) return;
        SetInfo* oldValue = _Set;
        _Set = value;
        OnChanged(oldValue, value, "Set");
    }

    void ItemInfo::SetItemStats(DBBindingList<ItemInfoStat>* value)
    {
        if (_ItemStats == value) return;
        DBBindingList<ItemInfoStat>* oldValue = _ItemStats;
        _ItemStats = value;
        OnChanged(oldValue, value, "ItemStats");
    }

    void ItemInfo::SetDrops(DBBindingList<DropInfo>* value)
    {
        if (_Drops == value) return;
        DBBindingList<DropInfo>* oldValue = _Drops;
        _Drops = value;
        OnChanged(oldValue, value, "Drops");
    }

    void ItemInfo::OnCreated()
    {
        DBObject::OnCreated();
        SetStackSize(1);
        SetRequiredGender(Library::RequiredGender::None);
        SetRequiredClass(Library::RequiredClass::All);
        SetSellRate(0.5);
        SetCanRepair(true);
        SetCanSell(true);
        SetCanStore(true);
        SetCanTrade(true);
        SetCanDrop(true);
        SetCanDeathDrop(true);
    }

    void ItemInfo::OnLoaded()
    {
        DBObject::OnLoaded();
        StatsChanged();
    }

    void ItemInfo::StatsChanged()
    {
        Stats.Clear();
        if (_ItemStats)
        {
            for (auto* stat : *_ItemStats)
                Stats[stat->GetStat()] += stat->GetAmount();
        }
    }
} // namespace Server::DBModels
