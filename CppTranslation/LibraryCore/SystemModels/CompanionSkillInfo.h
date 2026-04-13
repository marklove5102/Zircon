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
    class CompanionSkillInfo : DBObject
    {
        [IsIdentity]
        public int32_t Level
        {
            get { return _Level; }
            set
            {
                if (_Level == value) return;

                var oldValue = _Level;
                _Level = value;

                OnChanged(oldValue, value, "Level");
};
};
        private int32_t _Level;

        [IsIdentity]
        public Stat StatType
        {
            get { return _StatType; }
            set
            {
                if (_StatType == value) return;

                var oldValue = _StatType;
                _StatType = value;

                OnChanged(oldValue, value, "StatType");
};
};
        private Stat _StatType;
        
        public int32_t MaxAmount
        {
            get { return _MaxAmount; }
            set
            {
                if (_MaxAmount == value) return;

                var oldValue = _MaxAmount;
                _MaxAmount = value;

                OnChanged(oldValue, value, "MaxAmount");
};
};
        private int32_t _MaxAmount;

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
