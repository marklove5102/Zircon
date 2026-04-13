#pragma once
#include "DBObject.h"
#include "DBBindingList.h"
#include <string>

namespace Server::DBModels
{
    class ItemInfo;
    class SetInfoStats;

    public class SetInfo : public DBObject
    {
    private:
        std::string _SetName;
        DBBindingList<ItemInfo>* _Items = nullptr;
        DBBindingList<SetInfoStats>* _SetStats = nullptr;

    public:
        std::string GetSetName() const { return _SetName; }
        void SetSetName(const std::string& value);

        // Association("Set")
        DBBindingList<ItemInfo>* GetItems() const { return _Items; }
        void SetItems(DBBindingList<ItemInfo>* value);

        // Association("SetStats")
        DBBindingList<SetInfoStats>* GetSetStats() const { return _SetStats; }
        void SetSetStats(DBBindingList<SetInfoStats>* value);
    };
}
