#pragma once

#include "../Common/CSharpCompat.h"
#include "Enum.h"

namespace Library
{
    struct Frame
    {
        int Start;
        int Count;
        int Skip;
        std::vector<TimeSpan> Delays;
        bool Reversed = false;
        bool StaticSpeed = false;

        Frame() : Start(0), Count(0), Skip(0) {}
        Frame(int start, int count, int skip, TimeSpan delay)
            : Start(start), Count(count), Skip(skip)
        {
            Delays.resize(count, delay);
        }
    };

    class FrameSet
    {
    public:
        static std::unordered_map<MirAnimation, Frame> Players;
        static std::unordered_map<MirAnimation, Frame> DefaultItem;
        static std::unordered_map<MirAnimation, Frame> DefaultNPC;
        static std::unordered_map<MirAnimation, Frame> DefaultMonster;

        // Specific monster frame sets
        static std::unordered_map<MirAnimation, Frame> ForestYeti;
        static std::unordered_map<MirAnimation, Frame> ChestnutTree;
        static std::unordered_map<MirAnimation, Frame> CarnivorousPlant;
        static std::unordered_map<MirAnimation, Frame> DevouringGhost;
        static std::unordered_map<MirAnimation, Frame> Larva;
        static std::unordered_map<MirAnimation, Frame> ZumaGuardian;
        static std::unordered_map<MirAnimation, Frame> ZumaKing;
        static std::unordered_map<MirAnimation, Frame> Monkey;
        static std::unordered_map<MirAnimation, Frame> NumaMage;
        static std::unordered_map<MirAnimation, Frame> CursedCactus;
        static std::unordered_map<MirAnimation, Frame> NetherWorldGate;
        static std::unordered_map<MirAnimation, Frame> WestDesertLizard;
        static std::unordered_map<MirAnimation, Frame> BanyaGuard;
        static std::unordered_map<MirAnimation, Frame> EmperorSaWoo;
        static std::unordered_map<MirAnimation, Frame> JinchonDevil;
        static std::unordered_map<MirAnimation, Frame> ArchLichTaeda;
        static std::unordered_map<MirAnimation, Frame> ShinsuBig;
        static std::unordered_map<MirAnimation, Frame> PachonTheChaosBringer;
        static std::unordered_map<MirAnimation, Frame> IcySpiritGeneral;
        static std::unordered_map<MirAnimation, Frame> FieryDancer;
        static std::unordered_map<MirAnimation, Frame> EmeraldDancer;
        static std::unordered_map<MirAnimation, Frame> QueenOfDawn;
        static std::unordered_map<MirAnimation, Frame> JinamStoneGate;
        static std::unordered_map<MirAnimation, Frame> OYoungBeast;
        static std::unordered_map<MirAnimation, Frame> YumgonWitch;
        static std::unordered_map<MirAnimation, Frame> JinhwanSpirit;
        static std::unordered_map<MirAnimation, Frame> ChiwooGeneral;
        static std::unordered_map<MirAnimation, Frame> DragonQueen;
        static std::unordered_map<MirAnimation, Frame> DragonLord;
        static std::unordered_map<MirAnimation, Frame> FerociousIceTiger;
        static std::unordered_map<MirAnimation, Frame> SamaFireGuardian;
        static std::unordered_map<MirAnimation, Frame> Phoenix;
        static std::unordered_map<MirAnimation, Frame> EnshrinementBox;
        static std::unordered_map<MirAnimation, Frame> BloodStone;
        static std::unordered_map<MirAnimation, Frame> SamaCursedBladesman;
        static std::unordered_map<MirAnimation, Frame> SamaCursedSlave;
        static std::unordered_map<MirAnimation, Frame> SamaProphet;
        static std::unordered_map<MirAnimation, Frame> SamaSorcerer;
        static std::unordered_map<MirAnimation, Frame> EasterEvent;
        static std::unordered_map<MirAnimation, Frame> OrangeTiger;
        static std::unordered_map<MirAnimation, Frame> RedTiger;
        static std::unordered_map<MirAnimation, Frame> OrangeBossTiger;
        static std::unordered_map<MirAnimation, Frame> BigBossTiger;
        static std::unordered_map<MirAnimation, Frame> SDMob3;
        static std::unordered_map<MirAnimation, Frame> SDMob8;
        static std::unordered_map<MirAnimation, Frame> SDMob15;
        static std::unordered_map<MirAnimation, Frame> SDMob16;
        static std::unordered_map<MirAnimation, Frame> SDMob17;
        static std::unordered_map<MirAnimation, Frame> SDMob18;
        static std::unordered_map<MirAnimation, Frame> SDMob19;
        static std::unordered_map<MirAnimation, Frame> SDMob21;
        static std::unordered_map<MirAnimation, Frame> SDMob22;
        static std::unordered_map<MirAnimation, Frame> SDMob23;
        static std::unordered_map<MirAnimation, Frame> SDMob24;
        static std::unordered_map<MirAnimation, Frame> SDMob25;
        static std::unordered_map<MirAnimation, Frame> SDMob26;
        static std::unordered_map<MirAnimation, Frame> LobsterLord;
        static std::unordered_map<MirAnimation, Frame> LobsterSpawn;
        static std::unordered_map<MirAnimation, Frame> DeadTree;
        static std::unordered_map<MirAnimation, Frame> BobbitWorm;
        static std::unordered_map<MirAnimation, Frame> MonasteryMon1;
        static std::unordered_map<MirAnimation, Frame> MonasteryMon3;

        static void Initialize();
    };
}
