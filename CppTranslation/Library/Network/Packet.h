#pragma once

#include "../../Common/CSharpCompat.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <fstream>

namespace Library::Network
{
    // Forward declarations
    class Packet;

    // Attribute classes
    class IgnorePropertyPacket : public Attribute
    {
    };

    class CompleteObject : public Attribute
    {
    };

    // Main Packet base class
    class Packet
    {
    protected:
        static std::vector<Type<Packet>*> Packets;
        static std::unordered_map<Type<void>*, std::function<void(void*, BinaryWriter*)>> TypeWrite;
        static std::unordered_map<Type<void>*, std::function<void*(BinaryReader*)>> TypeRead;

    public:
        static bool IsClient;

        Type<Packet>* PacketType;
        int Length;
        bool ObserverPacket;

        static void Initialize();
        static Packet* ReceivePacket(std::vector<byte> rawBytes, std::vector<byte>& extra);
        std::vector<byte> GetPacketBytes();

    protected:
        static void WriteObject(BinaryWriter* writer, void* ob);
        static void ReadObject(BinaryReader* reader, void* ob);
        static void CompleteObjectMethod(void* ob);

    public:
        Packet();
        virtual ~Packet();

        template<typename T>
        static void RegisterTypeWrite(std::function<void(T, BinaryWriter*)> writeFunc)
        {
            Type<void>* type = typeof(T);
            TypeWrite[type] = [writeFunc](void* v, BinaryWriter* w) {
                writeFunc(*static_cast<T*>(v), w);
            };
        }

        template<typename T>
        static void RegisterTypeRead(std::function<T(BinaryReader*)> readFunc)
        {
            Type<void>* type = typeof(T);
            TypeRead[type] = [readFunc](BinaryReader* r) {
                T result = readFunc(r);
                return new T(result);
            };
        }
    };

} // namespace Library::Network
