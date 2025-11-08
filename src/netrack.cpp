// #include <pcap.h>
#include <print>
#include <thread>
#include "ConsumerPacket.hpp"
#include "Helper.hpp"
#include "ProducerPacket.hpp"

int main()
{
    std::string interface_name;
    Helper::findInterface(interface_name);

    constexpr int BUFFER_CAP = 16;
    RingBuffer shared_buffer(BUFFER_CAP);
    std::println("factory created, buffer cap: {0}", BUFFER_CAP);
    ProducerPacket pp(shared_buffer, interface_name);
    ConsumerPacket cp(shared_buffer);

    std::println("thread create");
    std::thread pt(&ProducerPacket::run, &pp);
    std::thread ct(&ConsumerPacket::run, &cp);

    pt.join();
    ct.join();

    std::println("simulation ended");
}
