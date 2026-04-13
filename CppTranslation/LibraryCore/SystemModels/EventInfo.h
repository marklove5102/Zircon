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
    #region World Event

    class WorldEventInfo : DBObject
    {
        [IsIdentity]
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

        public bool ResetWhenMax
        {
            get { return _ResetWhenMax; }
            set
            {
                if (_ResetWhenMax == value) return;

                var oldValue = _ResetWhenMax;
                _ResetWhenMax = value;

                OnChanged(oldValue, value, "ResetWhenMax");
};
};
        private bool _ResetWhenMax;

        [Association("Triggers", true)]
        DBBindingstd::vector<WorldEventTrigger> Triggers;

        [Association("Actions", true)]
        DBBindingstd::vector<WorldEventAction> Actions;
};

    class WorldEventTrigger : DBObject
    {
        [Association("Triggers")]
        public WorldEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private WorldEventInfo _Event;

        public WorldEventTriggerType Type
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
        private WorldEventTriggerType _Type;

        public int32_t Value
        {
            get { return _Value; }
            set
            {
                if (_Value == value) return;

                var oldValue = _Value;
                _Value = value;

                OnChanged(oldValue, value, "Value");
};
};
        private int32_t _Value;

        public int32_t MaxTriggers
        {
            get { return _MaxTriggers; }
            set
            {
                if (_MaxTriggers == value) return;

                var oldValue = _MaxTriggers;
                _MaxTriggers = value;

                OnChanged(oldValue, value, "MaxTriggers");
};
};
        private int32_t _MaxTriggers;
};

    class WorldEventAction : BaseEventAction
    {
        [Association("Actions")]
        public WorldEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private WorldEventInfo _Event;

        [Association("TriggerStats", true)]
        DBBindingstd::vector<WorldEventInfoTriggerStat> Stats;

        protected internal override void OnLoaded()
        {
            base.OnLoaded();

            StatsChanged();
};

        public void StatsChanged()
        {
            CalculatedStats.Clear();

            foreach (var stat in Stats)
                CalculatedStats[stat.Stat] += stat.Amount;
};
};

    class WorldEventInfoTriggerStat : DBObject
    {
        [IsIdentity]
        [Association("TriggerStats")]
        public WorldEventAction Action
        {
            get { return _Action; }
            set
            {
                if (_Action == value) return;

                var oldValue = _Action;
                _Action = value;

                OnChanged(oldValue, value, "Action");
};
};
        private WorldEventAction _Action;

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

    #endregion

    #region Player Event

    class PlayerEventInfo : DBObject
    {
        [IsIdentity]
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

        public EventTrackingType TrackingType
        {
            get { return _TrackingType; }
            set
            {
                if (_TrackingType == value) return;

                var oldValue = _TrackingType;
                _TrackingType = value;

                OnChanged(oldValue, value, "TrackingType");
};
};
        private EventTrackingType _TrackingType;

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

        public bool ResetWhenMax
        {
            get { return _ResetWhenMax; }
            set
            {
                if (_ResetWhenMax == value) return;

                var oldValue = _ResetWhenMax;
                _ResetWhenMax = value;

                OnChanged(oldValue, value, "ResetWhenMax");
};
};
        private bool _ResetWhenMax;

        [Association("Triggers", true)]
        DBBindingstd::vector<PlayerEventTrigger> Triggers;

        [Association("Actions", true)]
        DBBindingstd::vector<PlayerEventAction> Actions;
};

    class PlayerEventTrigger : DBObject
    {
        [Association("Triggers")]
        public PlayerEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private PlayerEventInfo _Event;

        public PlayerEventTriggerType Type
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
        private PlayerEventTriggerType _Type; 
        
        public int32_t Value
        {
            get { return _Value; }
            set
            {
                if (_Value == value) return;

                var oldValue = _Value;
                _Value = value;

                OnChanged(oldValue, value, "Value");
};
};
        private int32_t _Value;

        public std::string StringParameter1
        {
            get { return _StringParameter1; }
            set
            {
                if (_StringParameter1 == value) return;

                var oldValue = _StringParameter1;
                _StringParameter1 = value;

                OnChanged(oldValue, value, "StringParameter1");
};
};
        private std::string _StringParameter1;

        public MapInfo MapParameter1
        {
            get { return _MapParameter1; }
            set
            {
                if (_MapParameter1 == value) return;

                var oldValue = _MapParameter1;
                _MapParameter1 = value;

                OnChanged(oldValue, value, "MapParameter1");
};
};
        private MapInfo _MapParameter1;

        public MapRegion RegionParameter1
        {
            get { return _RegionParameter1; }
            set
            {
                if (_RegionParameter1 == value) return;

                var oldValue = _RegionParameter1;
                _RegionParameter1 = value;

                OnChanged(oldValue, value, "RegionParameter1");
};
};
        private MapRegion _RegionParameter1;

        public InstanceInfo InstanceParameter1
        {
            get { return _InstanceParameter1; }
            set
            {
                if (_InstanceParameter1 == value) return;

                var oldValue = _InstanceParameter1;
                _InstanceParameter1 = value;

                OnChanged(oldValue, value, "InstanceParameter1");
};
};
        private InstanceInfo _InstanceParameter1;

        public int32_t MaxTriggers
        {
            get { return _MaxTriggers; }
            set
            {
                if (_MaxTriggers == value) return;

                var oldValue = _MaxTriggers;
                _MaxTriggers = value;

                OnChanged(oldValue, value, "MaxTriggers");
};
};
        private int32_t _MaxTriggers;
};

    class PlayerEventAction : BaseEventAction
    {
        [Association("Actions")]
        public PlayerEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private PlayerEventInfo _Event;

        [Association("TriggerStats", true)]
        DBBindingstd::vector<PlayerEventInfoTriggerStat> Stats;

        protected internal override void OnLoaded()
        {
            base.OnLoaded();

            StatsChanged();
};

        public void StatsChanged()
        {
            CalculatedStats.Clear();

            foreach (var stat in Stats)
                CalculatedStats[stat.Stat] += stat.Amount;
};
};

    class PlayerEventInfoTriggerStat : DBObject
    {
        [IsIdentity]
        [Association("TriggerStats")]
        public PlayerEventAction Action
        {
            get { return _Action; }
            set
            {
                if (_Action == value) return;

                var oldValue = _Action;
                _Action = value;

                OnChanged(oldValue, value, "Action");
};
};
        private PlayerEventAction _Action;

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

    #endregion

    #region Monster Event

    class MonsterEventInfo : DBObject
    {
        [IsIdentity]
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

        public EventTrackingType TrackingType
        {
            get { return _TrackingType; }
            set
            {
                if (_TrackingType == value) return;

                var oldValue = _TrackingType;
                _TrackingType = value;

                OnChanged(oldValue, value, "TrackingType");
};
};
        private EventTrackingType _TrackingType;

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

        public bool ResetWhenMax
        {
            get { return _ResetWhenMax; }
            set
            {
                if (_ResetWhenMax == value) return;

                var oldValue = _ResetWhenMax;
                _ResetWhenMax = value;

                OnChanged(oldValue, value, "ResetWhenMax");
};
};
        private bool _ResetWhenMax;

        [Association("Triggers", true)]
        DBBindingstd::vector<MonsterEventTrigger> Triggers;

        [Association("Actions", true)]
        DBBindingstd::vector<MonsterEventAction> Actions;
};

    class MonsterEventTrigger : DBObject
    {
        [Association("Triggers")]
        public MonsterEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private MonsterEventInfo _Event;

        public MonsterEventTriggerType Type
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
        private MonsterEventTriggerType _Type;

        [Association("Events")]
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

        public MapInfo MapParameter1
        {
            get { return _MapParameter1; }
            set
            {
                if (_MapParameter1 == value) return;

                var oldValue = _MapParameter1;
                _MapParameter1 = value;

                OnChanged(oldValue, value, "MapParameter1");
};
};
        private MapInfo _MapParameter1;

        public MapRegion RegionParameter1
        {
            get { return _RegionParameter1; }
            set
            {
                if (_RegionParameter1 == value) return;

                var oldValue = _RegionParameter1;
                _RegionParameter1 = value;

                OnChanged(oldValue, value, "RegionParameter1");
};
};
        private MapRegion _RegionParameter1;

        public InstanceInfo InstanceParameter1
        {
            get { return _InstanceParameter1; }
            set
            {
                if (_InstanceParameter1 == value) return;

                var oldValue = _InstanceParameter1;
                _InstanceParameter1 = value;

                OnChanged(oldValue, value, "InstanceParameter1");
};
};
        private InstanceInfo _InstanceParameter1;

        public int32_t Value
        {
            get { return _Value; }
            set
            {
                if (_Value == value) return;

                var oldValue = _Value;
                _Value = value;

                OnChanged(oldValue, value, "Value");
};
};
        private int32_t _Value;

        public int32_t MaxTriggers
        {
            get { return _MaxTriggers; }
            set
            {
                if (_MaxTriggers == value) return;

                var oldValue = _MaxTriggers;
                _MaxTriggers = value;

                OnChanged(oldValue, value, "MaxTriggers");
};
};
        private int32_t _MaxTriggers;
};

    class MonsterEventAction : BaseEventAction
    {
        [Association("Actions")]
        public MonsterEventInfo Event
        {
            get { return _Event; }
            set
            {
                if (_Event == value) return;

                var oldValue = _Event;
                _Event = value;

                OnChanged(oldValue, value, "Event");
};
};
        private MonsterEventInfo _Event;

        [Association("TriggerStats", true)]
        DBBindingstd::vector<MonsterEventInfoTriggerStat> Stats;

        protected internal override void OnLoaded()
        {
            base.OnLoaded();

            StatsChanged();
};

        public void StatsChanged()
        {
            CalculatedStats.Clear();

            foreach (var stat in Stats)
                CalculatedStats[stat.Stat] += stat.Amount;
};
};

    class MonsterEventInfoTriggerStat : DBObject
    {
        [IsIdentity]
        [Association("TriggerStats")]
        public MonsterEventAction Action
        {
            get { return _Action; }
            set
            {
                if (_Action == value) return;

                var oldValue = _Action;
                _Action = value;

                OnChanged(oldValue, value, "Action");
};
};
        private MonsterEventAction _Action;

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

    #endregion

    #region Base Event

    class BaseEventAction : DBObject
    {
        public EventActionType Type
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
        private EventActionType _Type;

        public bool Restrict
        {
            get { return _Restrict; }
            set
            {
                if (_Restrict == value) return;

                var oldValue = _Restrict;
                _Restrict = value;

                OnChanged(oldValue, value, "Restrict");
};
};
        private bool _Restrict;

        public int32_t TriggerValue
        {
            get { return _TriggerValue; }
            set
            {
                if (_TriggerValue == value) return;

                var oldValue = _TriggerValue;
                _TriggerValue = value;

                OnChanged(oldValue, value, "TriggerValue");
};
};
        private int32_t _TriggerValue;

        public std::string StringParameter1
        {
            get { return _StringParameter1; }
            set
            {
                if (_StringParameter1 == value) return;

                var oldValue = _StringParameter1;
                _StringParameter1 = value;

                OnChanged(oldValue, value, "StringParameter1");
};
};
        private std::string _StringParameter1;

        public MonsterInfo MonsterParameter1
        {
            get { return _MonsterParameter1; }
            set
            {
                if (_MonsterParameter1 == value) return;

                var oldValue = _MonsterParameter1;
                _MonsterParameter1 = value;

                OnChanged(oldValue, value, "MonsterParameter1");
};
};
        private MonsterInfo _MonsterParameter1;

        public RespawnInfo RespawnParameter1
        {
            get { return _RespawnParameter1; }
            set
            {
                if (_RespawnParameter1 == value) return;

                var oldValue = _RespawnParameter1;
                _RespawnParameter1 = value;

                OnChanged(oldValue, value, "RespawnParameter1");
};
};
        private RespawnInfo _RespawnParameter1;

        public MapInfo MapParameter1
        {
            get { return _MapParameter1; }
            set
            {
                if (_MapParameter1 == value) return;

                var oldValue = _MapParameter1;
                _MapParameter1 = value;

                OnChanged(oldValue, value, "MapParameter1");
};
};
        private MapInfo _MapParameter1;

        public MapRegion RegionParameter1
        {
            get { return _RegionParameter1; }
            set
            {
                if (_RegionParameter1 == value) return;

                var oldValue = _RegionParameter1;
                _RegionParameter1 = value;

                OnChanged(oldValue, value, "RegionParameter1");
};
};
        private MapRegion _RegionParameter1;

        public InstanceInfo InstanceParameter1
        {
            get { return _InstanceParameter1; }
            set
            {
                if (_InstanceParameter1 == value) return;

                var oldValue = _InstanceParameter1;
                _InstanceParameter1 = value;

                OnChanged(oldValue, value, "InstanceParameter1");
};
};
        private InstanceInfo _InstanceParameter1;

        public ItemInfo ItemParameter1
        {
            get { return _ItemParameter1; }
            set
            {
                if (_ItemParameter1 == value) return;

                var oldValue = _ItemParameter1;
                _ItemParameter1 = value;

                OnChanged(oldValue, value, "ItemParameter1");
};
};
        private ItemInfo _ItemParameter1;

        public Stats CalculatedStats = new();
};

    #endregion

    #region Enums

    public enum EventTrackingType
    {
        Global = 0,
        Player = 1,
        Group = 2,
        Guild = 3,

        Instance = 10
};

    public enum WorldEventTriggerType
    {
        Dawn = 0,
        Day = 1,
        Dusk = 2,
        Night = 3,
};

    public enum PlayerEventTriggerType
    {
        PlayerEnter = 0,
        PlayerLeave = 1,
        PlayerDie = 2,
        PlayerCommand = 3,

        TimerMinute = 10,
};

    public enum MonsterEventTriggerType
    {
        MonsterDie = 0,
        MonsterClear = 1
};

    public enum EventActionType
    {
        MonsterSpawn = 0,
        MonsterPlayerSpawn = 1,
        MonsterBuffAdd = 2,
        MonsterBuffRemove = 3,

        PlayerMessage = 10,
        PlayerTeleport = 11,
        PlayerEscape = 12,
        PlayerBuffAdd = 13,
        PlayerBuffRemove = 14,

        TimerStart = 20,
        TimerStop = 21,
        TimerReset = 22,

        ItemDrop = 30,
        ItemGive = 31
};

    #endregion

    #region Event Log

    class EventLog
    {
        std::string Key;

        WorldEventInfo WorldEvent;
        PlayerEventInfo PlayerEvent;
        MonsterEventInfo MonsterEvent;

        int32_t PlayerIndex;

        InstanceInfo InstanceInfo;
        uint8_t InstanceSequence;

        public int32_t CurrentValue;

        std::unordered_map<WorldEventTrigger, int32_t> WorldTriggerCount; = [];
        std::unordered_map<PlayerEventTrigger, int32_t> PlayerTriggerCount; = [];
        std::unordered_map<MonsterEventTrigger, int32_t> MonsterTriggerCount; = [];

        public void Reset()
        {
            CurrentValue = 0;

            WorldTriggerCount.Clear();
            PlayerTriggerCount.Clear();
            MonsterTriggerCount.Clear();
};
};

    #endregion
};

}
