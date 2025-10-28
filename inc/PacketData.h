#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <stdint.h>
#include <cstdint>

struct PacketData
{
    const uint8_t* data;
    int len;
    PacketData() : data(nullptr), len(0) {}
    PacketData(const uint8_t* data, int length) : data(data), len(length) {}
};

#endif  // !PACKETDATA_H
