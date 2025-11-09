#ifndef ETHERNETHEADER_HPP
#define ETHERNETHEADER_HPP
#include <cstdlib>
#include <array>

#pragma pack(push,2)
struct EthernetHeader{
    std::array<uint8_t,6> dest_mac;
    std::array<uint8_t,6> source_mac;
    uint16_t ether_type;
};
#pragma pack(pop)

#endif
