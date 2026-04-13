#include "BaseConnection.h"
#include "../../Common/CSharpCompat.h"
#include <algorithm>

namespace Library::Network
{
    // Static members initialization
    std::unordered_map<std::string, DiagnosticValue*> BaseConnection::Diagnostics;
    std::unordered_map<Type<Packet>*, System::Reflection::MethodInfo*> BaseConnection::PacketMethods;
    bool BaseConnection::Monitor = false;

    // Duration property implementation
    TimeSpan BaseConnection::Duration() const
    {
        return Time::Now() - TimeConnected;
    }

    // Disconnecting property setter
    void BaseConnection::Disconnecting::set(bool value)
    {
        if (_disconnecting == value) return;
        _disconnecting = value;
        TimeOutTime = Time::Now() + TimeSpan::FromSeconds(2);
    }

    // Constructor
    BaseConnection::BaseConnection(TcpClient* client)
        : Client(client),
          Connected(false),
          Sending(false),
          TotalBytesSent(0),
          TotalBytesReceived(0),
          AdditionalLogging(false),
          TimeConnected(Time::Now()),
          TimeOutTime(),
          _disconnecting(false),
          ReceiveList(nullptr),
          SendList(nullptr)
    {
        // Note: TcpClient setup (NoDelay, etc.) should be done in derived class
        Connected = true;
        TimeConnected = Time::Now();
        
        // Initialize queues
        ReceiveList = new ConcurrentQueue<Packet*>();
        SendList = new ConcurrentQueue<Packet*>();
    }

    // Destructor
    BaseConnection::~BaseConnection()
    {
        delete ReceiveList;
        delete SendList;
        ReceiveList = nullptr;
        SendList = nullptr;
    }

    // BeginReceive method
    void BaseConnection::BeginReceive()
    {
        try
        {
            if (Client == nullptr || !Client->Connected()) return;

            // Note: Actual async receive implementation depends on network library used
            // This is a placeholder for the actual socket receive logic
            byte* rawBytes = new byte[8 * 1024];
            
            // In C++, you would use your networking library's async receive here
            // For example with Boost.Asio or similar
            // Client->Socket()->async_receive(...);
        }
        catch (const Exception& ex)
        {
            if (AdditionalLogging && OnException != nullptr)
                OnException->Invoke(this, const_cast<Exception*>(&ex));
            Disconnecting = true;
        }
    }

    // ReceiveData method
    void BaseConnection::ReceiveData(IAsyncResult* result)
    {
        try
        {
            if (!Connected) return;

            // Note: This is a simplified version. Actual implementation depends on networking library
            int dataRead = 0; // result->GetBytesRead(); // Placeholder
            
            if (dataRead == 0)
            {
                Disconnecting = true;
                return;
            }
            
            TotalBytesReceived += dataRead;
            UpdateTimeOut();

            // Combine existing raw data with new data
            size_t oldSize = _rawData.size();
            _rawData.resize(oldSize + dataRead);
            // Copy new data to end of buffer
            // Note: Actual copy logic depends on how data is received
            
            // Process packets from buffer
            Packet* p = nullptr;
            while ((p = Packet::ReceivePacket(_rawData)) != nullptr)
            {
                ReceiveList->Enqueue(p);
            }

            BeginReceive();
        }
        catch (const Exception& ex)
        {
            if (AdditionalLogging && OnException != nullptr)
                OnException->Invoke(this, const_cast<Exception*>(&ex));
            Disconnecting = true;
        }
    }

    // ProcessPacket method
    void BaseConnection::ProcessPacket(Packet* p)
    {
        if (p == nullptr) return;

        DateTime start = Time::Now();
        
        System::Reflection::MethodInfo* info = nullptr;
        auto typePtr = p->PacketType;
        
        auto it = PacketMethods.find(typePtr);
        if (it == PacketMethods.end())
        {
            // Note: Reflection in C++ requires custom implementation
            // This is a placeholder for finding the Process method
            // info = GetType()->GetMethod("Process", { p->PacketType });
            if (info == nullptr)
                throw NotImplementedException("Not Implemented Exception: Method Process.");
            
            PacketMethods[typePtr] = info;
        }

        if (info == nullptr)
            throw NotImplementedException("Not Implemented Exception: Method Process.");

        // Invoke the process method
        // info->Invoke(this, { p });

        if (!Monitor) return;

        TimeSpan execution = Time::Now() - start;
        DiagnosticValue* value = nullptr;
        std::string typeName = p->PacketType->FullName; // Placeholder

        it = Diagnostics.find(typeName);
        if (it == Diagnostics.end())
        {
            value = new DiagnosticValue();
            value->Name = typeName;
            Diagnostics[typeName] = value;
        }
        else
        {
            value = it->second;
        }

        value->Count++;
        value->TotalTime = value->TotalTime + execution;
        value->TotalSize += p->Length;

        if (execution > value->LargestTime)
            value->LargestTime = execution;

        if (p->Length > value->LargestSize)
            value->LargestSize = p->Length;
    }

    // UpdateTimeOut method
    void BaseConnection::UpdateTimeOut()
    {
        if (Disconnecting) return;
        TimeOutTime = Time::Now() + TimeOutDelay();
    }

    // Send method
    void BaseConnection::Send(Packet* packet)
    {
        if (!Connected || packet == nullptr) return;
        SendList->Enqueue(packet);
    }

    // ProcessSend method
    void BaseConnection::ProcessSend()
    {
        if (SendList == nullptr || SendList->IsEmpty()) return;
        
        std::vector<byte> data;
        
        while (!SendList->IsEmpty())
        {
            Packet* p = nullptr;
            if (!SendList->TryDequeue(&p)) continue;
            
            if (p == nullptr) continue;

            try
            {
                auto bytes = p->GetPacketBytes();
                data.insert(data.end(), bytes.begin(), bytes.end());
            }
            catch (const Exception& ex)
            {
                if (OnException != nullptr)
                    OnException->Invoke(this, const_cast<Exception*>(&ex));
                Disconnecting = true;
                return;
            }

            if (!Monitor) continue;
            
            DiagnosticValue* value = nullptr;
            auto typePtr = p->PacketType;
            std::string typeName = typePtr->FullName; // Placeholder
            
            auto it = Diagnostics.find(typeName);
            if (it == Diagnostics.end())
            {
                value = new DiagnosticValue();
                value->Name = typeName;
                Diagnostics[typeName] = value;
            }
            else
            {
                value = it->second;
            }

            value->Count++;
            value->TotalSize += p->Length;
            
            if (p->Length > value->LargestSize)
                value->LargestSize = p->Length;
        }
        
        if (!data.empty())
        {
            BeginSend(data);
        }
    }

    // DiagnosticValue methods
    long DiagnosticValue::TotalTicks() const
    {
        return TotalTime.Ticks;
    }

    long DiagnosticValue::TotalMilliseconds() const
    {
        return TotalTicks() / TimeSpan::TicksPerMillisecond;
    }

    long DiagnosticValue::LargestTicks() const
    {
        return LargestTime.Ticks;
    }

    long DiagnosticValue::LargestMilliseconds() const
    {
        return LargestTicks() / TimeSpan::TicksPerMillisecond;
    }

} // namespace Library::Network
