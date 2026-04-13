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
    class CurrencyInfo : DBObject
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

        public std::string Abbreviation
        {
            get { return _Abbreviation; }
            set
            {
                if (_Abbreviation == value) return;

                var oldValue = _Abbreviation;
                _Abbreviation = value;

                OnChanged(oldValue, value, "Abbreviation");
};
};
        private std::string _Abbreviation;

        public CurrencyType Type
        {
            get { return _Type; }
            set
            {
                if (_Type == value) return;

                var oldValue = _Type;
                _Type = value;

                OnChanged(oldValue, value, "Type");
};
};
        private CurrencyType _Type;

        public CurrencyCategory Category
        {
            get { return _Category; }
            set
            {
                if (_Category == value) return;

                var oldValue = _Category;
                _Category = value;

                OnChanged(oldValue, value, "Category");
};
};
        private CurrencyCategory _Category;

        public ItemInfo DropItem
        {
            get { return _DropItem; }
            set
            {
                if (_DropItem == value) return;

                var oldValue = _DropItem;
                _DropItem = value;

                OnChanged(oldValue, value, "DropItem");
};
};
        private ItemInfo _DropItem;

        public decimal ExchangeRate
        {
            get { return _ExchangeRate; }
            set
            {
                if (_ExchangeRate == value) return;

                var oldValue = _ExchangeRate;
                _ExchangeRate = value;

                OnChanged(oldValue, value, "ExchangeRate");
};
};
        private decimal _ExchangeRate;

        [Association("Images", true)]
        DBBindingstd::vector<CurrencyInfoImage> Images;

        protected internal override void OnCreated()
        {
            base.OnCreated();

            ExchangeRate = 1M;
};
};

    class CurrencyInfoImage : DBObject
    {
        [Association("Images")]
        public CurrencyInfo Currency
        {
            get { return _Currency; }
            set
            {
                if (_Currency == value) return;

                var oldValue = _Currency;
                _Currency = value;

                OnChanged(oldValue, value, "Currency");
};
};
        private CurrencyInfo _Currency;

        public int32_t Image
        {
            get { return _Image; }
            set
            {
                if (_Image == value) return;

                var oldValue = _Image;
                _Image = value;

                OnChanged(oldValue, value, "Image");
};
};
        private int32_t _Image;

        public int64_t Amount
        {
            get { return _Amount; }
            set
            {
                if (_Amount == value) return;

                var oldValue = _Amount;
                _Amount = value;

                OnChanged(oldValue, value, "Amount");
};
};
        private int64_t _Amount;
};
};

}
