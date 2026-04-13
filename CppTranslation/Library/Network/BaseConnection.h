#pragma once

#include "../../Common/CSharpCompat.h"
#include "Packet.h"
#include <unordered_map>
#include <string>

namespace Library::Network
{
    class DiagnosticValue;

    // Forward declare TcpClient equivalent
    class TcpClient;

    class BaseConnection
    {
    public:
        static std::unordered_map<std::string, DiagnosticValue*> Diagnostics;
        static std::unordered_map<Type<Packet>*, System::Reflection::MethodInfo*> PacketMethods;
        static bool Monitor;

        bool Connected;
    protected:
        bool Sending;

        int TotalBytesSent;
        int TotalBytesReceived;

        bool AdditionalLogging;

    protected:
        TcpClient* Client;

        DateTime TimeConnected;
        TimeSpan Duration() const;

    protected:
        virtual TimeSpan TimeOutDelay() = 0;

    public:
        DateTime TimeOutTime;

    private:
        bool _disconnecting;

    public:
        bool Disconnecting
        {
            get { return _disconnecting; }
            set;
        }

        ConcurrentQueue<Packet*>* ReceiveList;
        ConcurrentQueue<Packet*>* SendList;

    private:
        std::vector<byte> _rawData;

    public:
        EventHandler<Exception>* OnException;

    protected:
        BaseConnection(TcpClient* client);
        virtual ~BaseConnection();

    protected:
        void BeginReceive();
        void ReceiveData(IAsyncResult* result);
        void ProcessPacket(Packet* p);

    public:
        void UpdateTimeOut();
        virtual void Disconnect() = 0;
        virtual void Send(Packet* packet);

    protected:
        virtual void BeginSend(const std::vector<byte>& data) = 0;
        void ProcessSend();
    };

    class DiagnosticValue
    {
    public:
        std::string Name;
        TimeSpan TotalTime;
        TimeSpan LargestTime;
        int Count;
        long TotalSize;
        long LargestSize;

        long TotalTicks() const;
        long TotalMilliseconds() const;
        long LargestTicks() const;
        long LargestMilliseconds() const;
    };

} // namespace Library::Network
