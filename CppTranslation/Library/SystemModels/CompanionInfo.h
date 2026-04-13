#pragma once

#include "../MirDB/DBObject.h"
#include "../Stat.h"

namespace Library::SystemModels
{

class CompanionLevelInfo : public DBObject
{
private:
    int _Level;
    int _MaxExperience;
    int _InventorySpace;
    int _InventoryWeight;
    int _MaxHunger;

public:
    int GetLevel() const { return _Level; }
    void SetLevel(int value);

    int GetMaxExperience() const { return _MaxExperience; }
    void SetMaxExperience(int value);

    int GetInventorySpace() const { return _InventorySpace; }
    void SetInventorySpace(int value);

    int GetInventoryWeight() const { return _InventoryWeight; }
    void SetInventoryWeight(int value);

    int GetMaxHunger() const { return _MaxHunger; }
    void SetMaxHunger(int value);
};

class CompanionSkillInfo : public DBObject
{
private:
    int _Level;
    Stat _StatType;
    int _MaxAmount;
    int _Weight;

public:
    int GetLevel() const { return _Level; }
    void SetLevel(int value);

    Stat GetStatType() const { return _StatType; }
    void SetStatType(Stat value);

    int GetMaxAmount() const { return _MaxAmount; }
    void SetMaxAmount(int value);

    int GetWeight() const { return _Weight; }
    void SetWeight(int value);
};

} // namespace Library::SystemModels
