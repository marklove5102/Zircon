#include "SetInfo.h"

namespace Server::DBModels
{
    void SetInfo::SetSetName(const std::string& value)
    {
        if (_SetName == value) return;

        auto oldValue = _SetName;
        _SetName = value;

        OnChanged(oldValue, value, "SetName");
    }

    void SetInfo::SetItems(DBBindingList<ItemInfo>* value)
    {
        if (_Items == value) return;

        auto oldValue = _Items;
        _Items = value;

        OnChanged(oldValue, value, "Items");
    }

    void SetInfo::SetSetStats(DBBindingList<SetInfoStats>* value)
    {
        if (_SetStats == value) return;

        auto oldValue = _SetStats;
        _SetStats = value;

        OnChanged(oldValue, value, "SetStats");
    }
}
