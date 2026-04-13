#pragma once

#include "../MirDB/DBObject.h"
#include "../Enum.h"
#include "../Stat.h"

namespace Library::SystemModels
{

class WeaponCraftStatInfo : public DBObject
{
private:
    RequiredClass _RequiredClass;
    Stat _Stat;
    int _MinValue;
    int _MaxValue;
    int _Weight;

public:
    RequiredClass GetRequiredClass() const { return _RequiredClass; }
    void SetRequiredClass(RequiredClass value);

    Stat GetStat() const { return _Stat; }
    void SetStat(Stat value);

    int GetMinValue() const { return _MinValue; }
    void SetMinValue(int value);

    int GetMaxValue() const { return _MaxValue; }
    void SetMaxValue(int value);

    int GetWeight() const { return _Weight; }
    void SetWeight(int value);
};

} // namespace Library::SystemModels
