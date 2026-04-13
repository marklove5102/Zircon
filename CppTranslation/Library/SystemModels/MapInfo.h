#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"

namespace Library { namespace SystemModels {

class MapRegion;
class MineInfo;
class GuardInfo;
class MapInfo;

// MapInfo class
class MapInfo : public MirDB::DBObject
{
public:
    // Properties
    std::string GetFileName() const { return _FileName; }
    void SetFileName(const std::string& value);
    
    std::string GetDescription() const { return _Description; }
    void SetDescription(const std::string& value);
    
    int GetMiniMap() const { return _MiniMap; }
    void SetMiniMap(int value);
    
    LightSetting GetLight() const { return _Light; }
    void SetLight(LightSetting value);
    
    FightSetting GetFight() const { return _Fight; }
    void SetFight(FightSetting value);
    
    bool GetAllowRT() const { return _AllowRT; }
    void SetAllowRT(bool value);
    
    int GetSkillDelay() const { return _SkillDelay; }
    void SetSkillDelay(int value);
    
    bool GetCanHorse() const { return _CanHorse; }
    void SetCanHorse(bool value);
    
    bool GetAllowTT() const { return _AllowTT; }
    void SetAllowTT(bool value);
    
    bool GetCanMine() const { return _CanMine; }
    void SetCanMine(bool value);
    
    bool GetCanMarriageRecall() const { return _CanMarriageRecall; }
    void SetCanMarriageRecall(bool value);
    
    bool GetAllowRecall() const { return _AllowRecall; }
    void SetAllowRecall(bool value);
    
    int GetMinimumLevel() const { return _MinimumLevel; }
    void SetMinimumLevel(int value);
    
    int GetMaximumLevel() const { return _MaximumLevel; }
    void SetMaximumLevel(int value);
    
    MapInfo* GetReconnectMap() const { return _ReconnectMap; }
    void SetReconnectMap(MapInfo* value);
    
    SoundIndex GetMusic() const { return _Music; }
    void SetMusic(SoundIndex value);
    
    int GetMonsterHealth() const { return _MonsterHealth; }
    void SetMonsterHealth(int value);
    
    int GetMonsterDamage() const { return _MonsterDamage; }
    void SetMonsterDamage(int value);
    
    int GetDropRate() const { return _DropRate; }
    void SetDropRate(int value);
    
    int GetExperienceRate() const { return _ExperienceRate; }
    void SetExperienceRate(int value);
    
    int GetGoldRate() const { return _GoldRate; }
    void SetGoldRate(int value);
    
    int GetMaxMonsterHealth() const { return _MaxMonsterHealth; }
    void SetMaxMonsterHealth(int value);
    
    int GetMaxMonsterDamage() const { return _MaxMonsterDamage; }
    void SetMaxMonsterDamage(int value);
    
    int GetMaxDropRate() const { return _MaxDropRate; }
    void SetMaxDropRate(int value);
    
    int GetMaxExperienceRate() const { return _MaxExperienceRate; }
    void SetMaxExperienceRate(int value);
    
    int GetMaxGoldRate() const { return _MaxGoldRate; }
    void SetMaxGoldRate(int value);
    
    // Collections (DBBindingList equivalents)
    std::vector<GuardInfo*> Guards;
    std::vector<MapRegion*> Regions;
    std::vector<MineInfo*> Mining;
    
    // Public field (client variable)
    bool Expanded = true;
    
protected:
    void OnCreated() override;
    
private:
    std::string _FileName;
    std::string _Description;
    int _MiniMap = 0;
    LightSetting _Light;
    FightSetting _Fight;
    bool _AllowRT = true;
    int _SkillDelay = 0;
    bool _CanHorse = false;
    bool _AllowTT = true;
    bool _CanMine = false;
    bool _CanMarriageRecall = true;
    bool _AllowRecall = true;
    int _MinimumLevel = 0;
    int _MaximumLevel = 0;
    MapInfo* _ReconnectMap = nullptr;
    SoundIndex _Music;
    int _MonsterHealth = 0;
    int _MonsterDamage = 0;
    int _DropRate = 0;
    int _ExperienceRate = 0;
    int _GoldRate = 0;
    int _MaxMonsterHealth = 0;
    int _MaxMonsterDamage = 0;
    int _MaxDropRate = 0;
    int _MaxExperienceRate = 0;
    int _MaxGoldRate = 0;
};

}} // namespace Library::SystemModels
