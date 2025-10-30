#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <condition_variable>
#include <mutex>
#include <vector>
#include "PacketData.h"

class RingBuffer
{
private:
    std::mutex mtx;
    std::condition_variable not_full_cv;
    std::condition_variable not_empty_cv;
    std::vector<PacketData> packets;
    int head;
    int tail;
    int size;
    int capacity;

public:
    RingBuffer(const int c);
    bool tryPush(const PacketData& item);
    bool tryPop(PacketData& item);
    void pop(PacketData& item);
    void push(const PacketData& item);
    bool isEmpty();
    bool isEmptyLock();
    bool isFull();
    bool isFullLock();
    int getSize();
    int getSizeLock();
    int getCapacity();
    int getCapacityLock();
};

#endif  // !RINGBUFFER_H
