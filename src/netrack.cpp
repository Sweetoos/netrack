// #include <pcap.h>
#include <iostream>
#include "RingBuffer.h"

int main()
{
    const int capacity = 4;
    RingBuffer buffer(capacity);

    const uint8_t my_data[] = {0x00, 0x04, 0x08, 0x0C};

    if (buffer.tryPush(PacketData(my_data, sizeof(my_data))))
        std::cout << "buffer success, buffer size: " << buffer.getSize()
                  << std::endl;
    else
        std::cout << "buffer full" << std::endl;

    std::cout << "retrieving data" << std::endl;

    PacketData received;

    if (buffer.tryPop(received))
    {
        std::cout << "success, retrieved packet size: " << buffer.getSize()
                  << std::endl;
        if ((received.len == sizeof(my_data)) && (received.data[0] == 0x00))
            std::cout << "data is correct" << std::endl;
        else
            std::cout << "data is incorrect" << std::endl;
    }
    else
    {
        std::cout << "buffer is empty" << std::endl;
    }
}
