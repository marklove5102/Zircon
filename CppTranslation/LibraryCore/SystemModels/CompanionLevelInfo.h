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
    class CompanionLevelInfo : DBObject
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

        public int32_t MaxExperience
        {
            get { return _MaxExperience; }
            set
            {
                if (_MaxExperience == value) return;

                var oldValue = _MaxExperience;
                _MaxExperience = value;

                OnChanged(oldValue, value, "MaxExperience");
};
};
        private int32_t _MaxExperience;

        public int32_t InventorySpace
        {
            get { return _InventorySpace; }
            set
            {
                if (_InventorySpace == value) return;

                var oldValue = _InventorySpace;
                _InventorySpace = value;

                OnChanged(oldValue, value, "InventorySpace");
};
};
        private int32_t _InventorySpace;

        public int32_t InventoryWeight
        {
            get { return _InventoryWeight; }
            set
            {
                if (_InventoryWeight == value) return;

                var oldValue = _InventoryWeight;
                _InventoryWeight = value;

                OnChanged(oldValue, value, "InventoryWeight");
};
};
        private int32_t _InventoryWeight;

        public int32_t MaxHunger
        {
            get { return _MaxHunger; }
            set
            {
                if (_MaxHunger == value) return;

                var oldValue = _MaxHunger;
                _MaxHunger = value;

                OnChanged(oldValue, value, "MaxHunger");
};
};
        private int32_t _MaxHunger;
        
};
};

}
