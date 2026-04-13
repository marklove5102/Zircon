#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"

namespace Library { namespace SystemModels {

class MonsterInfoStat;
class RespawnInfo;
class DropInfo;
class EventTarget;
class QuestTaskMonsterDetails;

// MonsterInfo class
class MonsterInfo : public MirDB::DBObject
{
public:
    // Properties
    std::string GetMonsterName() const { return _MonsterName; }
    void SetMonsterName(const std::string& value);
    
    MonsterImage GetImage() const { return _Image; }
    void SetImage(MonsterImage value);
    
    int GetAI() const { return _AI; }
    void SetAI(int value);
    
    int GetLevel() const { return _Level; }
    void SetLevel(int value);
    
    int GetViewRange() const { return _ViewRange; }
    void SetViewRange(int value);
    
    int GetCoolEye() const { return _CoolEye; }
    void SetCoolEye(int value);
    
    decimal GetExperience() const { return _Experience; }
    void SetExperience(decimal value);
    
    bool GetUndead() const { return _Undead; }
    void SetUndead(bool value);
    
    bool GetCanPush() const { return _CanPush; }
    void SetCanPush(bool value);
    
    bool GetCanTame() const { return _CanTame; }
    void SetCanTame(bool value);
    
    int GetAttackDelay() const { return _AttackDelay; }
    void SetAttackDelay(int value);
    
    int GetMoveDelay() const { return _MoveDelay; }
    void SetMoveDelay(int value);
    
    bool GetIsBoss() const { return _IsBoss; }
    void SetIsBoss(bool value);
    
    MonsterFlag GetFlag() const { return _Flag; }
    void SetFlag(MonsterFlag value);
    
    // Public fields
    Stats Stats;
    
    // Collections (DBBindingList equivalents)
    std::vector<MonsterInfoStat*> MonsterInfoStats;
    std::vector<RespawnInfo*> Respawns;
    std::vector<DropInfo*> Drops;
    std::vector<EventTarget*> Events;
    std::vector<QuestTaskMonsterDetails*> QuestDetails;
    
protected:
    void OnCreated() override;
    void OnLoaded() override;
    
public:
    void StatsChanged();
    
private:
    std::string _MonsterName;
    MonsterImage _Image;
    int _AI = 0;
    int _Level = 0;
    int _ViewRange = 7;
    int _CoolEye = 0;
    decimal _Experience = 0;
    bool _Undead = false;
    bool _CanPush = true;
    bool _CanTame = false;
    int _AttackDelay = 2500;
    int _MoveDelay = 1800;
    bool _IsBoss = false;
    MonsterFlag _Flag;
};

}} // namespace Library::SystemModels
