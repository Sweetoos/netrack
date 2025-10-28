#include "ConsumerPacket.h"
#include <print>
#include <thread>
#include <chrono>

void ConsumerPacket::processPacket(const PacketData &packet)
{
    std::println("received packet no. {0} ", packet.len);
}

void ConsumerPacket::run()
{
    using namespace std::chrono_literals;
    while (true)
    {
        PacketData packet(nullptr, 0);
        buffer.tryPop(packet);
        processPacket(packet);
        std::this_thread::sleep_for(500ms);
    }
}
