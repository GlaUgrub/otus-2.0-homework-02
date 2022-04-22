#include <iostream>
#include "ip_tools.h"

void get_numerical_ip(const ip_addr_str_t& ip_str, ip_addr_num_t& ip_num)
{
    // TODO: check that valid IP address is present in "ip"

    int idx = 0;

    for (const auto& ip : ip_str)
    {
        // TODO: add range check for number
        ip_num.at(idx++) = static_cast<uint8_t>(std::stoi(ip));
    }
}

index_t generate_index(const ip_addr_num_t& ip_num)
{
    index_t index = 0;
    int shift = 24;

    for (unsigned int i = 0; i < ip_num.size(); i++, shift -= 8)
    {
        index |= (ip_num.at(i) << shift);
    }

    return index;
}

void generate_ip(index_t index, ip_addr_num_t& ip)
{
    int shift = 24;

    for (unsigned int i = 0; i < ip.size(); i++, shift -= 8)
    {
        ip.at(i) = (index >> shift);
    }
}

void print_ip(const ip_addr_num_t& ip)
{
    for (unsigned int i = 0; i < ip.size(); i++)
    {
        std::cout << std::dec <<+ip.at(i);
        if (i < ip.size() - 1)
        {
            std::cout << ".";
        }
    }

    std::cout << std::endl;
}