//
//  DnsCache.cpp
//  
//  Modified by 罗铮 on 03/26/14.

#include <map>
#include <string>
#include <mutex>
#include <thread>
#include <iostream>
#include <boost/thread/shared_mutex.hpp>

typedef std::string dns_entry;

class dns_cache
{
    std::map<std::string,dns_entry> entries;
    boost::shared_mutex entry_mutex;
public:
    dns_entry find_entry(std::string const& domain)
    {
        // This is the read lock
        boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
        std::map<std::string,dns_entry>::const_iterator const it=
            entries.find(domain);
        return (it==entries.end())?dns_entry():it->second;
    }
    void update_or_add_entry(std::string const& domain,
                             dns_entry const& dns_details)
    {
        // This is the write lock
        std::lock_guard<boost::shared_mutex> lk(entry_mutex);
        entries[domain]=dns_details;
    }
};

int main()
{
    dns_cache dc;

    std:: thread t1([&]{std::cout<<"found entry:"
      <<dc.find_entry("http://www.ubuntu.com")<<std::endl;});

    std:: thread t2([&]{std::cout<<"found entry:"
      <<dc.find_entry("http://www.ubuntu.com")<<std::endl;});

    std:: thread t3([&]{std::cout<<"found entry:"
      <<dc.find_entry("http://www.ubuntu.com")<<std::endl;});

    std:: thread t4([&]{std::cout<<"found entry:"
      <<dc.find_entry("http://www.ubuntu.com")<<std::endl;});

    std:: thread t5([&]{dc.update_or_add_entry("http://www.ubuntu.com",
      "91.189.90.59"); std::cout<<"entry added"<<std::endl;});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
