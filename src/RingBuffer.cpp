#include "RingBuffer.h"
#include <iostream>

RingBuffer::RingBuffer(const int c) : packets(c)
{
    this->size = 0;
    this->capacity = c;
    this->head = 0;
    this->tail = 0;
}

bool RingBuffer::tryPush(const PacketData &item)
{
    if (isFull()) return false;
    packets[head] = item;
    head = (head + 1) % capacity;
    size++;
    return true;
}

bool RingBuffer::tryPop(PacketData &item)
{
    if (isEmpty()) return false;
    item = packets[tail];
    tail = (tail + 1) % capacity;
    size--;
    return true;
}

bool RingBuffer::isEmpty() const { return this->size == 0; }

bool RingBuffer::isFull() const { return this->size == this->capacity; }

int RingBuffer::getSize() const { return this->size; }

int RingBuffer::getCapacity() const { return this->capacity; }
