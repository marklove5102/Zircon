#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"

namespace Server::DBModels
{
    class ItemInfo;

    class ItemInfoStat : public DBObject
    {
    private:
        ItemInfo* _Item = nullptr;
        Library::Stat _Stat = Library::Stat::None;
        int _Amount = 0;

    public:
        // Association("ItemStats")
        ItemInfo* GetItem() const { return _Item; }
        void SetItem(ItemInfo* value);

        Library::Stat GetStat() const { return _Stat; }
        void SetStat(Library::Stat value);

        int GetAmount() const { return _Amount; }
        void SetAmount(int value);
    };

} // namespace Server::DBModels
