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
    class BaseStat : DBObject
    {
        [IsIdentity]
        public MirClass Class
        {
            get { return _Class; }
            set
            {
                if (_Class == value) return;

                var oldValue = _Class;
                _Class = value;

                OnChanged(oldValue, value, "Class");
};
};
        private MirClass _Class;

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

        public int32_t Health
        {
            get { return _Health; }
            set
            {
                if (_Health == value) return;

                var oldValue = _Health;
                _Health = value;

                OnChanged(oldValue, value, "Health");
};
};
        private int32_t _Health;

        public int32_t Mana
        {
            get { return _Mana; }
            set
            {
                if (_Mana == value) return;

                var oldValue = _Mana;
                _Mana = value;

                OnChanged(oldValue, value, "Mana");
};
};
        private int32_t _Mana;

        public int32_t BagWeight
        {
            get { return _BagWeight; }
            set
            {
                if (_BagWeight == value) return;

                var oldValue = _BagWeight;
                _BagWeight = value;

                OnChanged(oldValue, value, "BagWeight");
};
};
        private int32_t _BagWeight;

        public int32_t WearWeight
        {
            get { return _WearWeight; }
            set
            {
                if (_WearWeight == value) return;

                var oldValue = _WearWeight;
                _WearWeight = value;

                OnChanged(oldValue, value, "WearWeight");
};
};
        private int32_t _WearWeight;

        public int32_t HandWeight
        {
            get { return _HandWeight; }
            set
            {
                if (_HandWeight == value) return;

                var oldValue = _HandWeight;
                _HandWeight = value;

                OnChanged(oldValue, value, "HandWeight");
};
};
        private int32_t _HandWeight;

        public int32_t Accuracy
        {
            get { return _Accuracy; }
            set
            {
                if (_Accuracy == value) return;

                var oldValue = _Accuracy;
                _Accuracy = value;

                OnChanged(oldValue, value, "Accuracy");
};
};
        private int32_t _Accuracy;

        public int32_t Agility
        {
            get { return _Agility; }
            set
            {
                if (_Agility == value) return;

                var oldValue = _Agility;
                _Agility = value;

                OnChanged(oldValue, value, "Agility");
};
};
        private int32_t _Agility;



        public int32_t MinAC
        {
            get { return _MinAC; }
            set
            {
                if (_MinAC == value) return;

                var oldValue = _MinAC;
                _MinAC = value;

                OnChanged(oldValue, value, "MinAC");
};
};
        private int32_t _MinAC;

        public int32_t MaxAC
        {
            get { return _MaxAC; }
            set
            {
                if (_MaxAC == value) return;

                var oldValue = _MaxAC;
                _MaxAC = value;

                OnChanged(oldValue, value, "MaxAC");
};
};
        private int32_t _MaxAC;

        public int32_t MinMR
        {
            get { return _MinMR; }
            set
            {
                if (_MinMR == value) return;

                var oldValue = _MinMR;
                _MinMR = value;

                OnChanged(oldValue, value, "MinMR");
};
};
        private int32_t _MinMR;

        public int32_t MaxMR
        {
            get { return _MaxMR; }
            set
            {
                if (_MaxMR == value) return;

                var oldValue = _MaxMR;
                _MaxMR = value;

                OnChanged(oldValue, value, "MaxMR");
};
};
        private int32_t _MaxMR;


        public int32_t MinDC
        {
            get { return _MinDC; }
            set
            {
                if (_MinDC == value) return;

                var oldValue = _MinDC;
                _MinDC = value;

                OnChanged(oldValue, value, "MinDC");
};
};
        private int32_t _MinDC;

        public int32_t MaxDC
        {
            get { return _MaxDC; }
            set
            {
                if (_MaxDC == value) return;

                var oldValue = _MaxDC;
                _MaxDC = value;

                OnChanged(oldValue, value, "MaxDC");
};
};
        private int32_t _MaxDC;


        public int32_t MinMC
        {
            get { return _MinMC; }
            set
            {
                if (_MinMC == value) return;

                var oldValue = _MinMC;
                _MinMC = value;

                OnChanged(oldValue, value, "MinMC");
};
};
        private int32_t _MinMC;

        public int32_t MaxMC
        {
            get { return _MaxMC; }
            set
            {
                if (_MaxMC == value) return;

                var oldValue = _MaxMC;
                _MaxMC = value;

                OnChanged(oldValue, value, "MaxMC");
};
};
        private int32_t _MaxMC;

        public int32_t MinSC
        {
            get { return _MinSC; }
            set
            {
                if (_MinSC == value) return;

                var oldValue = _MinSC;
                _MinSC = value;

                OnChanged(oldValue, value, "MinSC");
};
};
        private int32_t _MinSC;

        public int32_t MaxSC
        {
            get { return _MaxSC; }
            set
            {
                if (_MaxSC == value) return;

                var oldValue = _MaxSC;
                _MaxSC = value;

                OnChanged(oldValue, value, "MaxSC");
};
};
        private int32_t _MaxSC;
};
};

}
