#pragma once

#include "MapObject.h"
#include "LibraryCore/Enums.h"
#include <drawing.h>

namespace Library { class MirLibrary; }
namespace Library::Network::ServerPackets { struct ObjectSpell; }

namespace Client::Models
{

    class SpellObject : public MapObject
    {
    public:
        ObjectType Race() const override { return ObjectType::Spell; }
        bool Blocking() const override { return false; }

        SpellEffect Effect;

        Library::MirLibrary* BodyLibrary = nullptr;
        bool Blended = false;
        float BlendRate = 1.0f;

        int Power = 0;

        SpellObject(Library::Network::ServerPackets::ObjectSpell* info);

        void UpdateLibraries();
        void SetAnimation(ObjectAction* action) override;
        void Draw() override;
        bool MouseOver(Point p) override;
    };

} // namespace Client::Models
