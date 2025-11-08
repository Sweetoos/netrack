#ifndef HELPER_HPP
#define HELPER_HPP
#include <pcap/pcap.h>
#include <string>
#include <print>

namespace Helper
{
void findInterface(std::string &inteface_name)
{
    pcap_if_t* all_devs;
    char errbuf[PCAP_ERRBUF_SIZE];
    if(pcap_findalldevs(&all_devs, errbuf)==-1)
       return;
    
    for(pcap_if_t* dev=all_devs;dev!=nullptr;dev=dev->next)
    {
        if(dev->name==nullptr)    
            continue;

        bool is_up=dev->flags&PCAP_IF_UP;
        bool is_running=dev->flags&PCAP_IF_RUNNING;
        bool is_loopback=dev->flags&PCAP_IF_LOOPBACK;

        if(is_up&&is_running&&!is_loopback)
        {
            inteface_name=dev->name;
            break;
        }
    }
    pcap_freealldevs(all_devs);
}
};  // namespace Helper

#endif
