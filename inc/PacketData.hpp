#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <vector>
#include <cstdint>

struct PacketData
{
    std::vector<uint8_t> data;
    PacketData() = default;
    PacketData(const uint8_t* data, int length) : data(data, data + length) {}
};

#endif  // !PACKETDATA_H
