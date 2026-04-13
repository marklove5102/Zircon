#include "SetInfo.h"
#include "ItemInfo.h"
#include "SetInfoStat.h"

namespace Library { namespace SystemModels {

void SetInfo::SetSetName(const std::string& value)
{
    if (_SetName == value) return;
    
    auto oldValue = _SetName;
    _SetName = value;
    OnChanged(oldValue, value, "SetName");
}

}} // namespace Library::SystemModels
