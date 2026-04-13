#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"

namespace Library { namespace SystemModels {

class SetInfo;

// SetInfoStat class
class SetInfoStat : public MirDB::DBObject
{
public:
    // Properties
    SetInfo* GetSet() const { return _Set; }
    void SetSet(SetInfo* value);
    
    Stat GetStat() const { return _Stat; }
    void SetStat(Stat value);
    
    int GetAmount() const { return _Amount; }
    void SetAmount(int value);
    
    RequiredClass GetClass() const { return _Class; }
    void SetClass(RequiredClass value);
    
    int GetLevel() const { return _Level; }
    void SetLevel(int value);
    
protected:
    void OnCreated() override;
    
private:
    SetInfo* _Set = nullptr;
    Stat _Stat;
    int _Amount = 0;
    RequiredClass _Class = RequiredClass::All;
    int _Level = 0;
};

}} // namespace Library::SystemModels
