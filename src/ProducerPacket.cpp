#include "ProducerPacket.h"
#include <print>
#include <chrono>
#include <thread>

PacketData ProducerPacket::createFakePacket()
{
    packet_counter++;
    PacketData packet(0, packet_counter);
    std::println("created {0} packet ", packet_counter);
    return packet;
}

void ProducerPacket::run()
{
    using namespace std::chrono_literals;
    while (true)
    {
        PacketData packet = createFakePacket();
        buffer.tryPush(packet);
        std::this_thread::sleep_for(500ms);
    }
}
