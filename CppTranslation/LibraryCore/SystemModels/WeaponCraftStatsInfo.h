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
    class WeaponCraftStatInfo : DBObject
    {
        [IsIdentity]
        public RequiredClass RequiredClass
        {
            get { return _RequiredClass; }
            set
            {
                if (_RequiredClass == value) return;

                var oldValue = _RequiredClass;
                _RequiredClass = value;

                OnChanged(oldValue, value, "RequiredClass");
};
};
        private RequiredClass _RequiredClass;

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

        public int32_t MinValue
        {
            get { return _MinValue; }
            set
            {
                if (_MinValue == value) return;

                var oldValue = _MinValue;
                _MinValue = value;

                OnChanged(oldValue, value, "MinValue");
};
};
        private int32_t _MinValue;

        public int32_t MaxValue
        {
            get { return _MaxValue; }
            set
            {
                if (_MaxValue == value) return;

                var oldValue = _MaxValue;
                _MaxValue = value;

                OnChanged(oldValue, value, "MaxValue");
};
};
        private int32_t _MaxValue;

        [IsIdentity]
        public int32_t Weight
        {
            get { return _Weight; }
            set
            {
                if (_Weight == value) return;

                var oldValue = _Weight;
                _Weight = value;

                OnChanged(oldValue, value, "Weight");
};
};
        private int32_t _Weight;
        
};
};

}
