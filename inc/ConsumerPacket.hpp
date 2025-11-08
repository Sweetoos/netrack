#ifndef CONSUMERPACKET_H
#define CONSUMERPACKET_H

#include "PacketData.hpp"
#include "RingBuffer.hpp"

class ConsumerPacket
{
private:
    void processPacket(const PacketData &packet);
    RingBuffer &buffer;

public:
    ConsumerPacket(RingBuffer &buff) : buffer(buff) {}
    void run();
};

#endif
