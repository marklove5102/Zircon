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
    class FishingInfo : DBObject
    {
        [IsIdentity]
        public std::string Name
        {
            get { return _Name; }
            set
            {
                if (_Name == value) return;

                var oldValue = _Name;
                _Name = value;

                OnChanged(oldValue, value, "Name");
};
};
        private std::string _Name;

        public MapRegion Region
        {
            get { return _Region; }
            set
            {
                if (_Region == value) return;

                var oldValue = _Region;
                _Region = value;

                OnChanged(oldValue, value, "Region");
};
};
        private MapRegion _Region;

        [Association("Drops", true)]
        DBBindingstd::vector<FishingDropInfo> Drops;
};

    class FishingDropInfo : DBObject
    {
        [Association("Drops")]
        public FishingInfo Fishing
        {
            get { return _Fishing; }
            set
            {
                if (_Fishing == value) return;

                var oldValue = _Fishing;
                _Fishing = value;

                OnChanged(oldValue, value, "Fishing");
};
};
        private FishingInfo _Fishing;

        public ItemInfo Item
        {
            get { return _Item; }
            set
            {
                if (_Item == value) return;

                var oldValue = _Item;
                _Item = value;

                OnChanged(oldValue, value, "Item");
};
};
        private ItemInfo _Item;

        public int32_t Chance
        {
            get { return _Chance; }
            set
            {
                if (_Chance == value) return;

                var oldValue = _Chance;
                _Chance = value;

                OnChanged(oldValue, value, "Chance");
};
};
        private int32_t _Chance;

        public int32_t ThrowQuality
        {
            get { return _ThrowQuality; }
            set
            {
                if (_ThrowQuality == value) return;

                var oldValue = _ThrowQuality;
                _ThrowQuality = value;

                OnChanged(oldValue, value, "ThrowQuality");
};
};
        private int32_t _ThrowQuality;

        public bool PerfectCatch
        {
            get { return _PerfectCatch; }
            set
            {
                if (_PerfectCatch == value) return;

                var oldValue = _PerfectCatch;
                _PerfectCatch = value;

                OnChanged(oldValue, value, "PerfectCatch");
};
};
        private bool _PerfectCatch;
};
};

}
