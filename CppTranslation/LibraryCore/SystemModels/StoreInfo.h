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
    class StoreInfo : DBObject
    {
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

        public int32_t Price
        {
            get { return _Price; }
            set
            {
                if (_Price == value) return;

                var oldValue = _Price;
                _Price = value;

                OnChanged(oldValue, value, "Price");
};
};
        private int32_t _Price;

        public int32_t HuntGoldPrice
        {
            get => _HuntGoldPrice;
            set
            {
                if (_HuntGoldPrice == value) return;

                int32_t oldValue = _HuntGoldPrice;
                _HuntGoldPrice = value;

                OnChanged(oldValue, value, "HuntGoldPrice");
};
};
        private int32_t _HuntGoldPrice;
        
        public std::string Filter
        {
            get { return _Filter; }
            set
            {
                if (_Filter == value) return;

                var oldValue = _Filter;
                _Filter = value;

                OnChanged(oldValue, value, "Filter");
};
};
        private std::string _Filter;

        public bool Available
        {
            get { return _Available; }
            set
            {
                if (_Available == value) return;

                var oldValue = _Available;
                _Available = value;

                OnChanged(oldValue, value, "Available");
};
};
        private bool _Available;

        public int32_t Duration
        {
            get { return _Duration; }
            set
            {
                if (_Duration == value) return;

                var oldValue = _Duration;
                _Duration = value;

                OnChanged(oldValue, value, "Duration");
};
};
        private int32_t _Duration;
};

};

}
