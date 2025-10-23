#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>
#include "PacketData.h"

class RingBuffer
{
private:
    std::vector<PacketData> packets;
    int head;
    int tail;
    int size;
    int capacity;

public:
    RingBuffer(const int c);
    bool tryPush(const PacketData& item);
    bool tryPop(PacketData& item);
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    int getCapacity() const;
};

#endif  // !RINGBUFFER_H
