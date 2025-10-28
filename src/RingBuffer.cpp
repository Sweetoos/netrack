#include "RingBuffer.h"
#include <condition_variable>

RingBuffer::RingBuffer(const int c) : packets(c)
{
    this->size = 0;
    this->capacity = c;
    this->head = 0;
    this->tail = 0;
}

bool RingBuffer::tryPush(const PacketData &item)
{
    std::lock_guard lock(mtx);
    if (isFull()) return false;
    packets[head] = item;
    head = (head + 1) % capacity;
    size++;
    return true;
}

bool RingBuffer::tryPop(PacketData &item)
{
    std::lock_guard lock(mtx);
    if (isEmpty()) return false;
    item = packets[tail];
    tail = (tail + 1) % capacity;
    size--;
    return true;
}

bool RingBuffer::isEmpty() { return this->size == 0; }

bool RingBuffer::isFull() { return this->size == this->capacity; }

int RingBuffer::getSize() { return this->size; }

int RingBuffer::getCapacity() { return this->capacity; }

bool RingBuffer::isEmptyLock()
{
    std::lock_guard lock(mtx);
    return this->size == 0;
}

bool RingBuffer::isFullLock()
{
    std::lock_guard lock(mtx);
    return this->size == this->capacity;
}

int RingBuffer::getSizeLock()
{
    std::lock_guard lock(mtx);
    return this->size;
}

int RingBuffer::getCapacityLock()
{
    std::lock_guard lock(mtx);
    return this->capacity;
}
