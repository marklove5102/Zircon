#pragma once

#include "Packet.h"

namespace Library::Network::GeneralPackets
{
    // General network packets - these are sent first in the packet list
    
    class Connected : public Packet
    {
    };

    class Ping : public Packet
    {
    };

    class CheckVersion : public Packet
    {
    };

    class Version : public Packet
    {
    public:
        std::vector<byte> ClientHash;
    };

    class GoodVersion : public Packet
    {
    };

    class PingResponse : public Packet
    {
    public:
        int Ping;
    };

    class Disconnect : public Packet
    {
    public:
        DisconnectReason Reason;
    };

} // namespace Library::Network::GeneralPackets
