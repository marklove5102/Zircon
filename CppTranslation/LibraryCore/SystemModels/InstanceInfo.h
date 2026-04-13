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
    class InstanceInfo : DBObject
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

        public InstanceType Type
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
        private InstanceType _Type;

        public uint8_t MaxInstances
        {
            get { return _MaxInstances; }
            set
            {
                if (_MaxInstances == value) return;

                var oldValue = _MaxInstances;
                _MaxInstances = value;

                OnChanged(oldValue, value, "MaximumAllowed");
};
};
        private uint8_t _MaxInstances;

        public bool ShowOnDungeonFinder
        {
            get { return _ShowOnDungeonFinder; }
            set
            {
                if (_ShowOnDungeonFinder == value) return;

                var oldValue = _ShowOnDungeonFinder;
                _ShowOnDungeonFinder = value;

                OnChanged(oldValue, value, "ShowOnDungeonFinder");
};
};

        private bool _ShowOnDungeonFinder;
        public bool SafeZoneOnly
        {
            get { return _SafeZoneOnly; }
            set
            {
                if (_SafeZoneOnly == value) return;

                var oldValue = _SafeZoneOnly;
                _SafeZoneOnly = value;

                OnChanged(oldValue, value, "SafeZoneOnly");
};
};
        private bool _SafeZoneOnly;

        public bool AllowRejoin
        {
            get { return _AllowRejoin; }
            set
            {
                if (_AllowRejoin == value) return;

                var oldValue = _AllowRejoin;
                _AllowRejoin = value;

                OnChanged(oldValue, value, "AllowRejoin");
};
};
        private bool _AllowRejoin;

        public bool AllowTeleport
        {
            get { return _AllowTeleport; }
            set
            {
                if (_AllowTeleport == value) return;

                var oldValue = _AllowTeleport;
                _AllowTeleport = value;

                OnChanged(oldValue, value, "AllowTeleport");
};
};
        private bool _AllowTeleport;

        public bool SavePlace
        {
            get { return _SavePlace; }
            set
            {
                if (_SavePlace == value) return;

                var oldValue = _SavePlace;
                _SavePlace = value;

                OnChanged(oldValue, value, "SavePlace");
};
};
        private bool _SavePlace;

        public uint8_t MinPlayerLevel
        {
            get { return _MinPlayerLevel; }
            set
            {
                if (_MinPlayerLevel == value) return;

                var oldValue = _MinPlayerLevel;
                _MinPlayerLevel = value;

                OnChanged(oldValue, value, "MinimumLevel");
};
};
        private uint8_t _MinPlayerLevel;

        public uint8_t MaxPlayerLevel
        {
            get { return _MaxPlayerLevel; }
            set
            {
                if (_MaxPlayerLevel == value) return;

                var oldValue = _MaxPlayerLevel;
                _MaxPlayerLevel = value;

                OnChanged(oldValue, value, "MaximumLevel");
};
};
        private uint8_t _MaxPlayerLevel;

        public uint8_t MinPlayerCount
        {
            get { return _MinPlayerCount; }
            set
            {
                if (_MinPlayerCount == value) return;

                var oldValue = _MinPlayerCount;
                _MinPlayerCount = value;

                OnChanged(oldValue, value, "MinimumCount");
};
};
        private uint8_t _MinPlayerCount;

        public uint8_t MaxPlayerCount
        {
            get { return _MaxPlayerCount; }
            set
            {
                if (_MaxPlayerCount == value) return;

                var oldValue = _MaxPlayerCount;
                _MaxPlayerCount = value;

                OnChanged(oldValue, value, "MaximumCount");
};
};
        private uint8_t _MaxPlayerCount;

        public ItemInfo RequiredItem
        {
            get { return _RequiredItem; }
            set
            {
                if (_RequiredItem == value) return;

                var oldValue = _RequiredItem;
                _RequiredItem = value;

                OnChanged(oldValue, value, "RequiredItem");
};
};
        private ItemInfo _RequiredItem;

        public bool RequiredItemSingleUse
        {
            get { return _RequiredItemSingleUse; }
            set
            {
                if (_RequiredItemSingleUse == value) return;

                var oldValue = _RequiredItemSingleUse;
                _RequiredItemSingleUse = value;

                OnChanged(oldValue, value, "RequiredItemSingleUse");
};
};

        private bool _RequiredItemSingleUse;

        public MapRegion ConnectRegion
        {
            get { return _ConnectRegion; }
            set
            {
                if (_ConnectRegion == value) return;

                var oldValue = _ConnectRegion;
                _ConnectRegion = value;

                OnChanged(oldValue, value, "ConnectRegion");
};
};
        private MapRegion _ConnectRegion;

        public MapRegion ReconnectRegion
        {
            get { return _ReconnectRegion; }
            set
            {
                if (_ReconnectRegion == value) return;

                var oldValue = _ReconnectRegion;
                _ReconnectRegion = value;

                OnChanged(oldValue, value, "ReconnectRegion");
};
};
        private MapRegion _ReconnectRegion;

        public int32_t CooldownTimeInMinutes
        {
            get { return _CooldownTimeInMinutes; }
            set
            {
                if (_CooldownTimeInMinutes == value) return;

                var oldValue = _CooldownTimeInMinutes;
                _CooldownTimeInMinutes = value;

                OnChanged(oldValue, value, "CooldownTimeInMinutes");
};
};
        private int32_t _CooldownTimeInMinutes;

        public int32_t TimeLimitInMinutes
        {
            get { return _TimeLimitInMinutes; }
            set
            {
                if (_TimeLimitInMinutes == value) return;

                var oldValue = _TimeLimitInMinutes;
                _TimeLimitInMinutes = value;

                OnChanged(oldValue, value, "TimeLimitInMinutes");
};
};
        private int32_t _TimeLimitInMinutes;

        [Association("Map", true)]
        DBBindingstd::vector<InstanceMapInfo> Maps;

        [Association("InstanceInfoStats", true)]
        DBBindingstd::vector<InstanceInfoStat> BuffStats;

        [JsonIgnore]
        [IgnoreProperty]
        std::unordered_map<std::string, uint8_t> UserRecord;

        [JsonIgnore]
        [IgnoreProperty]
        std::unordered_map<std::string, DateTime> UserCooldown;

        [JsonIgnore]
        [IgnoreProperty]
        std::unordered_map<std::string, DateTime> GuildCooldown;

        public Stats Stats = new();

        protected internal override void OnLoaded()
        {
            base.OnLoaded();

            UserRecord = new std::unordered_map<std::string, uint8_t>();
            UserCooldown = new std::unordered_map<std::string, DateTime>();
            GuildCooldown = new std::unordered_map<std::string, DateTime>();

            StatsChanged();
};

        public void StatsChanged()
        {
            Stats.Clear();
            foreach (InstanceInfoStat stat in BuffStats)
                Stats[stat.Stat] += stat.Amount;
};
};

    class InstanceMapInfo : DBObject
    {
        [IsIdentity]
        [Association("Map")]
        public InstanceInfo Instance
        {
            get { return _Instance; }
            set
            {
                if (_Instance == value) return;

                var oldValue = _Instance;
                _Instance = value;

                OnChanged(oldValue, value, "Instance");
};
};
        private InstanceInfo _Instance;

        [IsIdentity]
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
};

    class InstanceInfoStat : DBObject
    {
        [IsIdentity]
        [Association("InstanceInfoStats")]
        public InstanceInfo Instance
        {
            get { return _Instance; }
            set
            {
                if (_Instance == value) return;

                var oldValue = _Instance;
                _Instance = value;

                OnChanged(oldValue, value, "Instance");
};
};
        private InstanceInfo _Instance;

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
};
}
