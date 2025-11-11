#ifndef IPHEADER_HPP
#define IPHEADER_HPP
#include <cstdlib>

#pragma pack(push, 1)
struct IPHeader
{
    uint8_t version_and_ihl;
    uint8_t dscp_and_ecn;
    uint16_t total_len;

    uint16_t identification;
    uint16_t flags_and_fragment_offset;

    uint8_t protocol;
    uint8_t ttl;
    uint16_t header_checksum;

    uint32_t dest_addr;

    uint32_t source_addr;
};
#pragma pack(pop)

static_assert(sizeof(IPHeader) == 20, "struct IPHeader must have 20 bytes");

#endif
