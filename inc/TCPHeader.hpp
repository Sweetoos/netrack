#ifndef TCPHEADER_HPP
#define TCPHEADER_HPP

#include <cstdlib>

#pragma pack(push, 1)
struct TCPHeader
{
    uint16_t source_port;
    uint16_t dest_port;
    uint32_t sequence_number;
    uint32_t acknowledgment_number;
    uint16_t checksum;
    uint8_t data_offset_and_reserved;
    uint8_t flags;
    uint16_t window;
    uint16_t urgent_pointer;
};
#pragma pack(pop)

static_assert(sizeof(TCPHeader) == 20, "struct TCPHeader must have 20 bytes");
#endif
