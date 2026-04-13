#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library::Network
{
namespace Library.Network.GeneralPackets
{
    class Connected : Packet { }
    class Ping : Packet { }
    class CheckVersion : Packet
    {
};
    class Version : Packet
    {
        public uint8_t[] ClientHash { get; set; }
};
    class GoodVersion : Packet
    {
        public uint8_t[] DatabaseKey { get; set; }
};
    class PingResponse : Packet
    {
        int32_t Ping;
};

    class Disconnect : Packet
    {
        DisconnectReason Reason;
};
};

}
