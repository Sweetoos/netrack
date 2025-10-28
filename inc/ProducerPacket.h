#ifndef PRODUCERPACKET_H
#define PRODUCERPACKET_H

#include "PacketData.h"
#include "RingBuffer.h"

class ProducerPacket
{
private:
    PacketData createFakePacket();
    RingBuffer& buffer;
    int packet_counter=0;

public:
    ProducerPacket(RingBuffer& buff) : buffer(buff) {}
    void run();
};

#endif
