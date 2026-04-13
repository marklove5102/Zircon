#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"
#include "../DBBindingList.h"

namespace Server::DBModels
{
    class SetInfo;
    class ItemInfoStat;
    class DropInfo;

    class ItemInfo : public DBObject
    {
    private:
        std::string _ItemName;
        Library::ItemType _ItemType = Library::ItemType::None;
        Library::RequiredClass _RequiredClass = Library::RequiredClass::All;
        Library::RequiredGender _RequiredGender = Library::RequiredGender::None;
        Library::RequiredType _RequiredType = Library::RequiredType::Level;
        int _RequiredAmount = 0;
        int _Shape = 0;
        Library::ItemEffect _Effect = Library::ItemEffect::None;
        int _Image = 0;
        int _Durability = 0;
        int _Price = 0;
        int _StackSize = 1;
        bool _StartItem = false;
        double _SellRate = 0.5;
        bool _CanRepair = true;
        bool _CanSell = true;
        bool _CanStore = true;
        bool _CanTrade = true;
        bool _CanDrop = true;
        bool _CanDeathDrop = true;
        std::string _Description;
        Library::Rarity _Rarity = Library::Rarity::Common;
        bool _CanAutoPot = false;
        SetInfo* _Set = nullptr;

    public:
        Library::Stats Stats;

        std::string GetItemName() const { return _ItemName; }
        void SetItemName(const std::string& value);

        Library::ItemType GetItemType() const { return _ItemType; }
        void SetItemType(Library::ItemType value);

        Library::RequiredClass GetRequiredClass() const { return _RequiredClass; }
        void SetRequiredClass(Library::RequiredClass value);

        Library::RequiredGender GetRequiredGender() const { return _RequiredGender; }
        void SetRequiredGender(Library::RequiredGender value);

        Library::RequiredType GetRequiredType() const { return _RequiredType; }
        void SetRequiredType(Library::RequiredType value);

        int GetRequiredAmount() const { return _RequiredAmount; }
        void SetRequiredAmount(int value);

        int GetShape() const { return _Shape; }
        void SetShape(int value);

        Library::ItemEffect GetEffect() const { return _Effect; }
        void SetEffect(Library::ItemEffect value);

        int GetImage() const { return _Image; }
        void SetImage(int value);

        int GetDurability() const { return _Durability; }
        void SetDurability(int value);

        int GetPrice() const { return _Price; }
        void SetPrice(int value);

        int GetStackSize() const { return _StackSize; }
        void SetStackSize(int value);

        bool GetStartItem() const { return _StartItem; }
        void SetStartItem(bool value);

        double GetSellRate() const { return _SellRate; }
        void SetSellRate(double value);

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

        Library::Rarity GetRarity() const { return _Rarity; }
        void SetRarity(Library::Rarity value);

        bool GetCanAutoPot() const { return _CanAutoPot; }
        void SetCanAutoPot(bool value);

        // Association("Set")
        SetInfo* GetSet() const { return _Set; }
        void SetSet(SetInfo* value);

        // Association("ItemStats")
        DBBindingList<ItemInfoStat>* GetItemStats() const { return _ItemStats; }
        void SetItemStats(DBBindingList<ItemInfoStat>* value);

        // Association("Drops", true)
        DBBindingList<DropInfo>* GetDrops() const { return _Drops; }
        void SetDrops(DBBindingList<DropInfo>* value);

    protected:
        void OnCreated() override;
        void OnLoaded() override;

    public:
        void StatsChanged();

    private:
        DBBindingList<ItemInfoStat>* _ItemStats = nullptr;
        DBBindingList<DropInfo>* _Drops = nullptr;
    };

} // namespace Server::DBModels
