#ifndef UDPHEADER_H
#define UDPHEADER_H

#include <cstdlib>

#pragma pack(push, 1)
struct UDPHeader
{
    uint16_t source_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
};
#pragma pack(pop)

static_assert(sizeof(UDPHeader) == 8, "struct UDPHeader must have 8 bytes");

#endif
