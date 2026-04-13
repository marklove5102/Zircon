#pragma once

#include "../MirDB/DBObject.h"
#include "ItemInfo.h"
#include <string>

namespace Library::SystemModels
{

class StoreInfo : public DBObject
{
private:
    ItemInfo* _Item;
    int _Price;
    int _HuntGoldPrice;
    std::string _Filter;
    bool _Available;
    int _Duration;

public:
    ItemInfo* GetItem() const { return _Item; }
    void SetItem(ItemInfo* value);

    int GetPrice() const { return _Price; }
    void SetPrice(int value);

    int GetHuntGoldPrice() const { return _HuntGoldPrice; }
    void SetHuntGoldPrice(int value);

    std::string GetFilter() const { return _Filter; }
    void SetFilter(const std::string& value);

    bool GetAvailable() const { return _Available; }
    void SetAvailable(bool value);

    int GetDuration() const { return _Duration; }
    void SetDuration(int value);
};

} // namespace Library::SystemModels
