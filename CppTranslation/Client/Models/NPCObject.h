#pragma once

#include "MapObject.h"
#include "LibraryCore/Enums.h"
#include "Library/SystemModels/NPCInfo.h"
#include "Client/Models/MirEffect.h"
#include <unordered_map>
#include <vector>

namespace Library { class MirLibrary; }
namespace Client::Controls { class DXLabel; }
namespace Library::Network::ServerPackets { struct ObjectNPC; }

namespace Client::Models
{

    class NPCObject : public MapObject
    {
    public:
        static std::unordered_map<Library::SystemModels::NPCInfo*, NPCObject*> NPCs;

        ObjectType Race() const override { return ObjectType::NPC; }

        CurrentQuest* CurrentQuest = nullptr;
        MirEffect* QuestEffect = nullptr;

        Library::SystemModels::NPCInfo* NPCInfo = nullptr;

        Library::MirLibrary* BodyLibrary = nullptr;
        int BodyOffSet = 100;
        int BodyShape = 0;
        int BodyFrame() const { return DrawFrame + BodyShape * BodyOffSet; }

        NPCObject(Library::Network::ServerPackets::ObjectNPC* info);

        void SetAnimation(ObjectAction* action) override;
        void NameChanged() override;
        void Draw() override;
        void DrawBlend() override;
        bool MouseOver(Point p) override;
        void UpdateQuests() override;
        void RemoveQuestEffect();
        void Remove() override;

    private:
        void DrawShadow();
        void DrawBody();
    };

} // namespace Client::Models
