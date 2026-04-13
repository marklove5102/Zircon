#pragma once
#include "../MirDB/DBObject.h"

namespace Library { namespace SystemModels {

class ItemInfo;
class SetInfoStat;

// SetInfo class
class SetInfo : public MirDB::DBObject
{
public:
    // Properties
    std::string GetSetName() const { return _SetName; }
    void SetSetName(const std::string& value);
    
    // Collections (DBBindingList equivalents)
    std::vector<ItemInfo*> Items;
    std::vector<SetInfoStat*> SetStats;
    
private:
    std::string _SetName;
};

}} // namespace Library::SystemModels
