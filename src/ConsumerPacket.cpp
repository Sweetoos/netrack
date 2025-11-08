#include "ConsumerPacket.hpp"
#include <chrono>
#include <print>
#include <thread>

void ConsumerPacket::processPacket(const PacketData &packet)
{
    if (!packet.data.empty())
    {
        uint8_t packet_id = packet.data[0];
        std::println("received packet no. {0} ", packet_id);
    }
}

void ConsumerPacket::run()
{
    using namespace std::chrono_literals;
    while (true)
    {
        PacketData packet(nullptr, 0);
        buffer.pop(packet);
        processPacket(packet);
        std::this_thread::sleep_for(500ms);
    }
}
