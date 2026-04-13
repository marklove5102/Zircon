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
    class MineInfo : DBObject
    {
        [IsIdentity]
        [Association("Mining")]
        public MapInfo Map
        {
            get { return _Map; }
            set
            {
                if (_Map == value) return;

                var oldValue = _Map;
                _Map = value;

                OnChanged(oldValue, value, "Map");
};
};
        private MapInfo _Map;

        [IsIdentity]
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

        public int32_t Quantity
        {
            get { return _Quantity; }
            set
            {
                if (_Quantity == value) return;

                var oldValue = _Quantity;
                _Quantity = value;

                OnChanged(oldValue, value, "Quantity");
};
};
        private int32_t _Quantity = -1;

        public int32_t RestockTimeInMinutes
        {
            get { return _RestockTimeInMinutes; }
            set
            {
                if (_RestockTimeInMinutes == value) return;

                var oldValue = _RestockTimeInMinutes;
                _RestockTimeInMinutes = value;

                OnChanged(oldValue, value, "RestockTimeInMinutes");
};
};
        private int32_t _RestockTimeInMinutes = -1;

        public int32_t RemainingQuantity;
        public DateTime NextRestock = DateTime.MaxValue;

        protected internal override void OnLoaded()
        {
            base.OnLoaded();

            RemainingQuantity = Quantity;
};
};
};

}
