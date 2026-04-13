#include "Packet.h"
#include "../../Common/CSharpCompat.h"
#include <algorithm>
#include <sstream>

namespace Library::Network
{
    // Static member initialization
    std::vector<Type<Packet>*> Packet::Packets;
    std::unordered_map<Type<void>*, std::function<void(void*, BinaryWriter*)>> Packet::TypeWrite;
    std::unordered_map<Type<void>*, std::function<void*(BinaryReader*)>> Packet::TypeRead;
    bool Packet::IsClient = false;

    void Packet::Initialize()
    {
        Packets.clear();
        
        // In C++, we need to manually register packet types or use reflection library
        // This is a placeholder - actual implementation would require a registration mechanism
        // similar to C#'s Assembly.GetExecutingAssembly().GetTypes()
        
        // Sort packets: GeneralPackets first, then by name
        std::sort(Packets.begin(), Packets.end(), [](Type<Packet>* t1, Type<Packet>* t2) {
            std::string ns1 = t1->Namespace();
            std::string ns2 = t2->Namespace();
            std::string name1 = t1->Name();
            std::string name2 = t2->Name();
            
            if (ns1 == ns2)
                return name1 < name2;
            
            if (ns1 == "Library.Network.GeneralPackets")
                return true;
            if (ns2 == "Library.Network.GeneralPackets")
                return false;
            
            return name1 < name2;
        });

        // Register basic type writers
        TypeWrite[typeof(bool)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<bool*>(v)); };
        TypeWrite[typeof(byte)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<byte*>(v)); };
        TypeWrite[typeof(std::vector<byte>)] = [](void* v, BinaryWriter* w) {
            auto& arr = *static_cast<std::vector<byte>*>(v);
            w->Write(static_cast<int>(arr.size()));
            w->Write(arr.data(), arr.size());
        };
        TypeWrite[typeof(char16_t)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<char16_t*>(v)); };
        TypeWrite[typeof(int)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<int*>(v)); };
        TypeWrite[typeof(long long)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<long long*>(v)); };
        TypeWrite[typeof(float)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<float*>(v)); };
        TypeWrite[typeof(double)] = [](void* v, BinaryWriter* w) { w->Write(*static_cast<double*>(v)); };
        TypeWrite[typeof(std::string)] = [](void* v, BinaryWriter* w) {
            const std::string& str = *static_cast<std::string*>(v);
            w->Write(str.c_str(), str.length());
        };

        // Register basic type readers
        TypeRead[typeof(bool)] = [](BinaryReader* r) {
            bool* v = new bool(r->ReadBoolean());
            return v;
        };
        TypeRead[typeof(byte)] = [](BinaryReader* r) {
            byte* v = new byte(r->ReadByte());
            return v;
        };
        TypeRead[typeof(std::vector<byte>)] = [](BinaryReader* r) {
            int len = r->ReadInt32();
            auto* v = new std::vector<byte>(len);
            r->Read(v->data(), len);
            return v;
        };
        TypeRead[typeof(int)] = [](BinaryReader* r) {
            int* v = new int(r->ReadInt32());
            return v;
        };
        TypeRead[typeof(long long)] = [](BinaryReader* r) {
            long long* v = new long long(r->ReadInt64());
            return v;
        };
        TypeRead[typeof(float)] = [](BinaryReader* r) {
            float* v = new float(r->ReadSingle());
            return v;
        };
        TypeRead[typeof(double)] = [](BinaryReader* r) {
            double* v = new double(r->ReadDouble());
            return v;
        };
        TypeRead[typeof(std::string)] = [](BinaryReader* r) {
            // Read string - implementation depends on how strings are stored
            std::string str;
            // Placeholder - actual implementation needs to know string length
            return new std::string(str);
        };
    }

    Packet* Packet::ReceivePacket(std::vector<byte> rawBytes, std::vector<byte>& extra)
    {
        extra = rawBytes;

        Packet* p = nullptr;

        if (rawBytes.size() < 4)
            return nullptr;

        // Little-endian length reading
        int length = (rawBytes[3] << 24) | (rawBytes[2] << 16) | (rawBytes[1] << 8) | rawBytes[0];

        if (length > static_cast<int>(rawBytes.size()))
            return nullptr;

        extra.resize(rawBytes.size() - length);
        std::copy(rawBytes.begin() + length, rawBytes.end(), extra.begin());

        // Create reader from bytes
        std::istringstream iss(std::string(rawBytes.begin(), rawBytes.end()));
        BinaryReader reader(&iss);
        reader.Seek(4, SeekOrigin::Begin);

        short id = reader.ReadInt16();
        if (id >= 0 && id < static_cast<short>(Packets.size()))
        {
            // Create instance - requires factory pattern in C++
            // p = Packets[id]->CreateInstance();
            // p->PacketType = Packets[id];
            // ReadObject(&reader, p);
        }

        if (p)
            p->Length = length;

        return p;
    }

    std::vector<byte> Packet::GetPacketBytes()
    {
        std::vector<byte> packet;
        
        // Write packet data
        std::ostringstream oss;
        BinaryWriter writer(&oss);
        
        // Find packet ID
        auto it = std::find(Packets.begin(), Packets.end(), this->PacketType);
        short id = (it != Packets.end()) ? static_cast<short>(std::distance(Packets.begin(), it)) : -1;
        
        writer.Write(id);
        WriteObject(&writer, this);
        
        // Get packet data
        std::string data = oss.str();
        packet.assign(data.begin(), data.end());
        
        Length = static_cast<int>(packet.size());
        
        // Prepend length
        std::ostringstream finalStream;
        BinaryWriter finalWriter(&finalStream);
        finalWriter.Write(Length + 4);
        finalWriter.Write(packet.data(), packet.size());
        
        std::string finalData = finalStream.str();
        return std::vector<byte>(finalData.begin(), finalData.end());
    }

    void Packet::WriteObject(BinaryWriter* writer, void* ob)
    {
        // Implementation requires reflection - use RTTI or custom reflection system
        // This is a simplified placeholder
        Type<void>* type = typeof(ob);
        auto properties = type->GetProperties();
        
        for (auto* prop : properties)
        {
            // Check for IgnorePropertyPacket attribute
            if (prop->HasAttribute<IgnorePropertyPacket>())
                continue;
            
            Type<void>* propType = prop->PropertyType();
            auto writeIt = TypeWrite.find(propType);
            
            if (writeIt == TypeWrite.end())
            {
                // Handle complex types
                if (propType->IsClass())
                {
                    void* value = prop->GetValue(ob);
                    writer->Write(value != nullptr);
                    if (value == nullptr)
                        continue;
                    
                    WriteObject(writer, value);
                }
                else if (propType->IsEnum())
                {
                    // Handle enum by writing underlying type
                    Type<void>* underlying = propType->GetEnumUnderlyingType();
                    auto underlyingWrite = TypeWrite.find(underlying);
                    if (underlyingWrite != TypeWrite.end())
                    {
                        void* value = prop->GetValue(ob);
                        underlyingWrite->second(value, writer);
                    }
                }
                // Handle List<> and other generic types...
            }
            else
            {
                void* value = prop->GetValue(ob);
                writeIt->second(value, writer);
            }
        }
    }

    void Packet::ReadObject(BinaryReader* reader, void* ob)
    {
        Type<void>* type = typeof(ob);
        auto properties = type->GetProperties();
        
        for (auto* prop : properties)
        {
            if (prop->HasAttribute<IgnorePropertyPacket>())
                continue;
            
            Type<void>* propType = prop->PropertyType();
            auto readIt = TypeRead.find(propType);
            
            if (readIt == TypeRead.end())
            {
                if (propType->IsClass())
                {
                    if (!reader->ReadBoolean())
                        continue;
                    
                    void* newValue = propType->CreateInstance();
                    prop->SetValue(ob, newValue);
                    ReadObject(reader, newValue);
                }
                else if (propType->IsEnum())
                {
                    Type<void>* underlying = propType->GetEnumUnderlyingType();
                    auto underlyingRead = TypeRead.find(underlying);
                    if (underlyingRead != TypeRead.end())
                    {
                        void* value = underlyingRead->second(reader);
                        prop->SetValue(ob, value);
                    }
                }
                // Handle List<> and other generic types...
            }
            else
            {
                void* value = readIt->second(reader);
                prop->SetValue(ob, value);
            }
        }
        
        // Call CompleteObject methods
        auto methods = type->GetMethods();
        for (auto* method : methods)
        {
            if (method->HasAttribute<CompleteObject>())
            {
                method->Invoke(ob, nullptr);
            }
        }
    }

    void Packet::CompleteObjectMethod(void* ob)
    {
        // Helper for calling CompleteObject attributed methods
    }

    Packet::Packet()
        : PacketType(nullptr), Length(0), ObserverPacket(true)
    {
    }

    Packet::~Packet()
    {
    }

} // namespace Library::Network
