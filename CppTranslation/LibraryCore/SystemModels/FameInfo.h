#pragma once
#include "../Enum.h"
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library
{




namespace Library.SystemModels
{
    class FameInfo : DBObject
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

        public int32_t Shape
        {
            get { return _Shape; }
            set
            {
                if (_Shape == value) return;

                var oldValue = _Shape;
                _Shape = value;

                OnChanged(oldValue, value, "Shape");
};
};
        private int32_t _Shape;

        public std::string Description
        {
            get { return _Description; }
            set
            {
                if (_Description == value) return;

                var oldValue = _Description;
                _Description = value;

                OnChanged(oldValue, value, "Description");
};
};
        private std::string _Description;

        public int32_t Cost
        {
            get { return _Cost; }
            set
            {
                if (_Cost == value) return;

                var oldValue = _Cost;
                _Cost = value;

                OnChanged(oldValue, value, "Cost");
};
};
        private int32_t _Cost;

        public int32_t Order
        {
            get { return _Order; }
            set
            {
                if (_Order == value) return;

                var oldValue = _Order;
                _Order = value;

                OnChanged(oldValue, value, "Order");
};
};
        private int32_t _Order;

        [Association("FameInfoStats", true)]
        DBBindingstd::vector<FameInfoStat> BuffStats;

        [Association("FameInfoRewards", true)]
        DBBindingstd::vector<FameInfoReward> ItemRewards;
};

    class FameInfoStat : DBObject
    {
        [IsIdentity]
        [Association("FameInfoStats")]
        public FameInfo Fame
        {
            get { return _Fame; }
            set
            {
                if (_Fame == value) return;

                var oldValue = _Fame;
                _Fame = value;

                OnChanged(oldValue, value, "Fame");
};
};
        private FameInfo _Fame;

        [IsIdentity]
        public Stat Stat
        {
            get { return _Stat; }
            set
            {
                if (_Stat == value) return;

                var oldValue = _Stat;
                _Stat = value;

                OnChanged(oldValue, value, "Stat");
};
};
        private Stat _Stat;

        public int32_t Amount
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
        private int32_t _Amount;
};

    class FameInfoReward : DBObject
    {
        [IsIdentity]
        [Association("FameInfoRewards")]
        public FameInfo Fame
        {
            get { return _Fame; }
            set
            {
                if (_Fame == value) return;

                var oldValue = _Fame;
                _Fame = value;

                OnChanged(oldValue, value, "Fame");
};
};
        private FameInfo _Fame;

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

        public int32_t Amount
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
        private int32_t _Amount;
};
};

}
