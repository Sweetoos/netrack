#ifndef CONSUMERPACKET_H
#define CONSUMERPACKET_H

#include "PacketData.hpp"
#include "RingBuffer.hpp"

class ConsumerPacket
{
private:
    void processPacket(const PacketData &packet);
    RingBuffer &buffer;
    void parseIPv4Packet(const uint8_t *ip_packet_data, size_t total_len);

public:
    ConsumerPacket(RingBuffer &buff) : buffer(buff) {}
    void run();
};

#endif
