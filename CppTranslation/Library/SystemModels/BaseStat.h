#pragma once

#include "../MirDB/DBObject.h"
#include "../../LibraryCore/Enum.h"

namespace Library::SystemModels
{
    class BaseStat : public MirDB::DBObject
    {
    private:
        MirClass _Class;
        int _Level;
        int _Health;
        int _Mana;
        int _BagWeight;
        int _WearWeight;
        int _HandWeight;
        int _Accuracy;
        int _Agility;
        int _MinAC;
        int _MaxAC;
        int _MinMR;
        int _MaxMR;
        int _MinDC;
        int _MaxDC;
        int _MinMC;
        int _MaxMC;
        int _MinSC;
        int _MaxSC;

    public:
        // Properties with getters and setters
        MirClass Class() const { return _Class; }
        void SetClass(MirClass value);

        int Level() const { return _Level; }
        void SetLevel(int value);

        int Health() const { return _Health; }
        void SetHealth(int value);

        int Mana() const { return _Mana; }
        void SetMana(int value);

        int BagWeight() const { return _BagWeight; }
        void SetBagWeight(int value);

        int WearWeight() const { return _WearWeight; }
        void SetWearWeight(int value);

        int HandWeight() const { return _HandWeight; }
        void SetHandWeight(int value);

        int Accuracy() const { return _Accuracy; }
        void SetAccuracy(int value);

        int Agility() const { return _Agility; }
        void SetAgility(int value);

        int MinAC() const { return _MinAC; }
        void SetMinAC(int value);

        int MaxAC() const { return _MaxAC; }
        void SetMaxAC(int value);

        int MinMR() const { return _MinMR; }
        void SetMinMR(int value);

        int MaxMR() const { return _MaxMR; }
        void SetMaxMR(int value);

        int MinDC() const { return _MinDC; }
        void SetMinDC(int value);

        int MaxDC() const { return _MaxDC; }
        void SetMaxDC(int value);

        int MinMC() const { return _MinMC; }
        void SetMinMC(int value);

        int MaxMC() const { return _MaxMC; }
        void SetMaxMC(int value);

        int MinSC() const { return _MinSC; }
        void SetMinSC(int value);

        int MaxSC() const { return _MaxSC; }
        void SetMaxSC(int value);
    };

} // namespace Library::SystemModels
