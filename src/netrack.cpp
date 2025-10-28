// #include <pcap.h>
#include <print>
#include <thread>
#include "ConsumerPacket.h"
#include "ProducerPacket.h"

int main()
{
    constexpr int BUFFER_CAP = 16;
    RingBuffer shared_buffer(BUFFER_CAP);
    std::println("factory created, buffer cap: {0}", BUFFER_CAP);
    ProducerPacket pp(shared_buffer);
    ConsumerPacket cp(shared_buffer);

    std::println("thread create");
    std::thread pt(&ProducerPacket::run, &pp);
    std::thread ct(&ConsumerPacket::run, &cp);

    pt.join();
    ct.join();

    std::println("simulation ended");
}
