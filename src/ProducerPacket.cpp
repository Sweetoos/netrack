#include "ProducerPacket.hpp"
#include <pcap/pcap.h>
#include <chrono>
#include <print>
#include <thread>

PacketData ProducerPacket::createFakePacket()
{
    PacketData packet;
    packet.data.resize(20);
    packet.data[0] = packet_counter;
    std::println("created {0} packet ", packet_counter);
    packet_counter++;
    return packet;
}

void ProducerPacket::run()
{
    using namespace std::chrono_literals;

    if (interface_name.empty())
    {
        std::println("Error: No network interface found");
        return;
    }

    pcap_handler =
        pcap_open_live(interface_name.c_str(), BUFSIZ, 1, 1000, errbuf);

    if (pcap_handler == nullptr)
    {
        std::println("Error opening interface {}: {}", interface_name, errbuf);
        return;
    }

    while (true)
    {
        int result = pcap_next_ex(pcap_handler, &header, &packet_data);
        if (result == 1)
        {
            if (header != nullptr && packet_data != nullptr)
            {
                PacketData packet(packet_data, header->len);
                buffer.push(packet);
            }
        }
        else if (result == 0)
            continue;
        else
        {
            pcap_perror(pcap_handler, " packet not captured\n");
            break;
        }
        std::this_thread::sleep_for(500ms);
    }

    if (pcap_handler != nullptr)
    {
        pcap_close(pcap_handler);
        pcap_handler = nullptr;
    }
}
