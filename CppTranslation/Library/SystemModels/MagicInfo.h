#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"

namespace Library { namespace SystemModels {

// MagicInfo class
class MagicInfo : public MirDB::DBObject
{
public:
    // Properties
    std::string GetName() const { return _Name; }
    void SetName(const std::string& value);
    
    MagicType GetMagic() const { return _Magic; }
    void SetMagic(MagicType value);
    
    MirClass GetClass() const { return _Class; }
    void SetClass(MirClass value);
    
    MagicSchool GetSchool() const { return _School; }
    void SetSchool(MagicSchool value);
    
    int GetIcon() const { return _Icon; }
    void SetIcon(int value);
    
    int GetMinBasePower() const { return _MinBasePower; }
    void SetMinBasePower(int value);
    
    int GetMaxBasePower() const { return _MaxBasePower; }
    void SetMaxBasePower(int value);
    
    int GetMinLevelPower() const { return _MinLevelPower; }
    void SetMinLevelPower(int value);
    
    int GetMaxLevelPower() const { return _MaxLevelPower; }
    void SetMaxLevelPower(int value);
    
    int GetBaseCost() const { return _BaseCost; }
    void SetBaseCost(int value);
    
    int GetLevelCost() const { return _LevelCost; }
    void SetLevelCost(int value);
    
    int GetNeedLevel1() const { return _NeedLevel1; }
    void SetNeedLevel1(int value);
    
    int GetNeedLevel2() const { return _NeedLevel2; }
    void SetNeedLevel2(int value);
    
    int GetNeedLevel3() const { return _NeedLevel3; }
    void SetNeedLevel3(int value);
    
    int GetExperience1() const { return _Experience1; }
    void SetExperience1(int value);
    
    int GetExperience2() const { return _Experience2; }
    void SetExperience2(int value);
    
    int GetExperience3() const { return _Experience3; }
    void SetExperience3(int value);
    
    int GetDelay() const { return _Delay; }
    void SetDelay(int value);
    
    std::string GetDescription() const { return _Description; }
    void SetDescription(const std::string& value);
    
private:
    std::string _Name;
    MagicType _Magic;
    MirClass _Class;
    MagicSchool _School;
    int _Icon = 0;
    int _MinBasePower = 0;
    int _MaxBasePower = 0;
    int _MinLevelPower = 0;
    int _MaxLevelPower = 0;
    int _BaseCost = 0;
    int _LevelCost = 0;
    int _NeedLevel1 = 0;
    int _NeedLevel2 = 0;
    int _NeedLevel3 = 0;
    int _Experience1 = 0;
    int _Experience2 = 0;
    int _Experience3 = 0;
    int _Delay = 0;
    std::string _Description;
};

}} // namespace Library::SystemModels
