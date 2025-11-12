#ifndef STATSMANAGER_HPP
#define STATSMANAGER_HPP

#include <cstdlib>

class StatsManager
{
private:

public:
    StatsManager();
    void packetProcessed(size_t bytes);
    void protocolCount(uint16_t ether_type, uint8_t ip_protocol);
    void printReport();
};

#endif
