#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library
{



namespace Library.SystemModels
{
    class SetInfo : DBObject
    {
        [IsIdentity]
        public std::string SetName
        {
            get { return _SetName; }
            set
            {
                if (_SetName == value) return;

                var oldValue = _SetName;
                _SetName = value;

                OnChanged(oldValue, value, "SetName");
};
};
        private std::string _SetName;

        [JsonIgnore]
        [Association("Set")]
        DBBindingstd::vector<ItemInfo> Items;

        [Association("SetStats")]
        DBBindingstd::vector<SetInfoStat> SetStats;
};
};

}
