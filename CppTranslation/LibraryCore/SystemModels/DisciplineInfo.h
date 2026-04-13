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
    class DisciplineInfo : DBObject
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

        public int32_t RequiredLevel
        {
            get { return _RequiredLevel; }
            set
            {
                if (_RequiredLevel == value) return;

                var oldValue = _RequiredLevel;
                _RequiredLevel = value;

                OnChanged(oldValue, value, "RequiredLevel");
};
};
        private int32_t _RequiredLevel;

        public int64_t RequiredExperience
        {
            get { return _RequiredExperience; }
            set
            {
                if (_RequiredExperience == value) return;

                var oldValue = _RequiredExperience;
                _RequiredExperience = value;

                OnChanged(oldValue, value, "RequiredExperience");
};
};
        private int64_t _RequiredExperience;

        public int32_t RequiredGold
        {
            get { return _RequiredGold; }
            set
            {
                if (_RequiredGold == value) return;

                var oldValue = _RequiredGold;
                _RequiredGold = value;

                OnChanged(oldValue, value, "RequiredGold");
};
};
        private int32_t _RequiredGold;

        public int32_t FocusPoints
        {
            get { return _FocusPoints; }
            set
            {
                if (_FocusPoints == value) return;

                var oldValue = _FocusPoints;
                _FocusPoints = value;

                OnChanged(oldValue, value, "FocusPoints");
};
};
        private int32_t _FocusPoints;
};
};

}
