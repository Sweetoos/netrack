#include "ConsumerPacket.hpp"
#include <arpa/inet.h>
#include <array>
#include <print>
#include "EthernetHeader.hpp"
#include "IPHeader.hpp"

void ConsumerPacket::processPacket(const PacketData &packet)
{
    if (packet.data.size() < sizeof(EthernetHeader))
    {
        return;
    }
    const uint8_t *raw_data = packet.data.data();
    const EthernetHeader *eth_header =
        reinterpret_cast<const EthernetHeader *>(raw_data);
    uint16_t ether_type = ntohs(eth_header->ether_type);
    std::println("Captured frame, size: {}, EtherType: 0x{:x}, ",
                 packet.data.size(), ether_type);
    switch (ether_type)
    {
        case 0x800:  // IPv4
        {
            const uint8_t *ip_data_start =
                packet.data.data() + sizeof(EthernetHeader);
            size_t remaining_len = packet.data.size() - sizeof(EthernetHeader);
            parseIPv4Packet(ip_data_start, remaining_len);
        }
        break;

        case 0x806:  // ARP
            std::println(" (ARP)");
            break;
        case 0x86dd:  // IPv6
            std::println(" (IPv6)");
            break;
    }
}
void ConsumerPacket::parseIPv4Packet(const uint8_t *ip_packet_data,
                                     size_t total_len)
{
    if (total_len < sizeof(IPHeader))
    {
        return;
    }
    const IPHeader *ip_header =
        reinterpret_cast<const IPHeader *>(ip_packet_data);

    uint8_t ttl = ip_header->ttl;
    uint32_t source_addr = ip_header->source_addr;
    uint32_t dest_addr = ip_header->dest_addr;

    std::array<char, INET_ADDRSTRLEN> source_ip_buffer;
    std::array<char, INET_ADDRSTRLEN> dest_ip_buffer;

    inet_ntop(AF_INET, &(ip_header->source_addr), source_ip_buffer.data(),
              source_ip_buffer.size());
    inet_ntop(AF_INET, &(ip_header->dest_addr), dest_ip_buffer.data(),
              dest_ip_buffer.size());

    std::println("-> IPv4 from: {}, to {}, TTL: {}", source_ip_buffer.data(),
                 dest_ip_buffer.data(), static_cast<int>(ip_header->ttl));
}
void ConsumerPacket::run()
{
    while (true)
    {
        PacketData packet(nullptr, 0);
        buffer.pop(packet);
        processPacket(packet);
    }
}
