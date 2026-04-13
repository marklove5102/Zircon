#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"
#include "SetInfo.h"
#include "ItemInfoStat.h"
#include "DropInfo.h"
#include "../Stat.h"

namespace Library { namespace SystemModels {

class ItemInfo : public MirDB::DBObject
{
public:
    // Properties
    std::string GetItemName() const { return _ItemName; }
    void SetItemName(const std::string& value);
    
    ItemType GetItemType() const { return _ItemType; }
    void SetItemType(ItemType value);
    
    RequiredClass GetRequiredClass() const { return _RequiredClass; }
    void SetRequiredClass(RequiredClass value);
    
    RequiredGender GetRequiredGender() const { return _RequiredGender; }
    void SetRequiredGender(RequiredGender value);
    
    RequiredType GetRequiredType() const { return _RequiredType; }
    void SetRequiredType(RequiredType value);
    
    int GetRequiredAmount() const { return _RequiredAmount; }
    void SetRequiredAmount(int value);
    
    int GetShape() const { return _Shape; }
    void SetShape(int value);
    
    ItemEffect GetEffect() const { return _Effect; }
    void SetEffect(ItemEffect value);
    
    int GetImage() const { return _Image; }
    void SetImage(int value);
    
    int GetDurability() const { return _Durability; }
    void SetDurability(int value);
    
    int GetPrice() const { return _Price; }
    void SetPrice(int value);
    
    int GetWeight() const { return _Weight; }
    void SetWeight(int value);
    
    int GetStackSize() const { return _StackSize; }
    void SetStackSize(int value);
    
    bool GetStartItem() const { return _StartItem; }
    void SetStartItem(bool value);
    
    decimal GetSellRate() const { return _SellRate; }
    void SetSellRate(decimal value);
    
    bool GetCanRepair() const { return _CanRepair; }
    void SetCanRepair(bool value);
    
    bool GetCanSell() const { return _CanSell; }
    void SetCanSell(bool value);
    
    bool GetCanStore() const { return _CanStore; }
    void SetCanStore(bool value);
    
    bool GetCanTrade() const { return _CanTrade; }
    void SetCanTrade(bool value);
    
    bool GetCanDrop() const { return _CanDrop; }
    void SetCanDrop(bool value);
    
    bool GetCanDeathDrop() const { return _CanDeathDrop; }
    void SetCanDeathDrop(bool value);
    
    std::string GetDescription() const { return _Description; }
    void SetDescription(const std::string& value);
    
    Rarity GetRarity() const { return _Rarity; }
    void SetRarity(Rarity value);
    
    bool GetCanAutoPot() const { return _CanAutoPot; }
    void SetCanAutoPot(bool value);
    
    int GetBuffIcon() const { return _BuffIcon; }
    void SetBuffIcon(int value);
    
    int GetPartCount() const { return _PartCount; }
    void SetPartCount(int value);
    
    SetInfo* GetSet() const { return _Set; }
    void SetSet(SetInfo* value);
    
    // Public fields
    Stats Stats;
    
    // Collections (DBBindingList equivalents)
    std::vector<ItemInfoStat*> ItemStats;
    std::vector<DropInfo*> Drops;
    
    // Computed property
    bool GetShouldLinkInfo() const { return StackSize > 1 || ItemType == ItemType::Consumable || ItemType == ItemType::Scroll; }
    
protected:
    void OnCreated() override;
    void OnLoaded() override;
    
public:
    void StatsChanged();
    std::string ToString() const override;
    
private:
    std::string _ItemName;
    ItemType _ItemType;
    RequiredClass _RequiredClass;
    RequiredGender _RequiredGender;
    RequiredType _RequiredType;
    int _RequiredAmount = 0;
    int _Shape = 0;
    ItemEffect _Effect;
    int _Image = 0;
    int _Durability = 0;
    int _Price = 0;
    int _Weight = 0;
    int _StackSize = 1;
    bool _StartItem = false;
    decimal _SellRate = 0.5M;
    bool _CanRepair = true;
    bool _CanSell = true;
    bool _CanStore = true;
    bool _CanTrade = true;
    bool _CanDrop = true;
    bool _CanDeathDrop = false;
    std::string _Description;
    Rarity _Rarity;
    bool _CanAutoPot = false;
    int _BuffIcon = 0;
    int _PartCount = 0;
    SetInfo* _Set = nullptr;
};

}} // namespace Library::SystemModels
