#ifndef PRODUCERPACKET_H
#define PRODUCERPACKET_H

#include <pcap/pcap.h>
#include <string>
#include "PacketData.hpp"
#include "RingBuffer.hpp"

class ProducerPacket
{
private:
    PacketData createFakePacket();
    RingBuffer& buffer;
    int packet_counter = 0;
    std::string interface_name;
    pcap_t* pcap_handler = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr* header;
    const uint8_t* packet_data;

public:
    ProducerPacket(RingBuffer& buff, const std::string& interface_name)
        : buffer(buff),
          interface_name(interface_name),
          header(nullptr),
          packet_data(nullptr)
    {
    }
    void run();
};

#endif
