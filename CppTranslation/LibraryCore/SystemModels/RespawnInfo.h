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
    class RespawnInfo : DBObject
    {
        [IsIdentity]
        [Association("Respawns")]
        public MonsterInfo Monster
        {
            get { return _Monster; }
            set
            {
                if (_Monster == value) return;

                var oldValue = _Monster;
                _Monster = value;

                OnChanged(oldValue, value, "Monster");
};
};
        private MonsterInfo _Monster;

        [IsIdentity]
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

        public bool EventSpawn
        {
            get { return _EventSpawn; }
            set
            {
                if (_EventSpawn == value) return;

                var oldValue = _EventSpawn;
                _EventSpawn = value;

                OnChanged(oldValue, value, "EventSpawn");
};
};
        private bool _EventSpawn;
           
        public int32_t Delay
        {
            get { return _Delay; }
            set
            {
                if (_Delay == value) return;

                var oldValue = _Delay;
                _Delay = value;

                OnChanged(oldValue, value, "Delay");
};
};
        private int32_t _Delay;
        
        public int32_t Count
        {
            get { return _Count; }
            set
            {
                if (_Count == value) return;

                var oldValue = _Count;
                _Count = value;

                OnChanged(oldValue, value, "Count");
};
};
        private int32_t _Count;

        public int32_t DropSet
        {
            get { return _DropSet; }
            set
            {
                if (_DropSet == value) return;

                var oldValue = _DropSet;
                _DropSet = value;

                OnChanged(oldValue, value, "DropSet");
};
};
        private int32_t _DropSet;

        public bool Announce
        {
            get { return _Announce; }
            set
            {
                if (_Announce == value) return;

                var oldValue = _Announce;
                _Announce = value;

                OnChanged(oldValue, value, "Announce");
};
};
        private bool _Announce;

        public int32_t EasterEventChance
        {
            get { return _EasterEventChance; }
            set
            {
                if (_EasterEventChance == value) return;

                var oldValue = _EasterEventChance;
                _EasterEventChance = value;

                OnChanged(oldValue, value, "EasterEventChance");
};
};
        private int32_t _EasterEventChance;

        public int32_t RespawnIndex
        {
            get { return _RespawnIndex; }
            set
            {
                if (_RespawnIndex == value) return;

                var oldValue = _RespawnIndex;
                _RespawnIndex = value;

                OnChanged(oldValue, value, "RespawnIndex");
};
};
        private int32_t _RespawnIndex;

        [JsonIgnore]
        [IgnoreProperty]
        public std::string RegionName => Region?.ServerDescription ?? std::string.Empty;

        [JsonIgnore]
        [IgnoreProperty]
        public std::string MonsterName => Monster?.MonsterName ?? std::string.Empty;
};
};

}
