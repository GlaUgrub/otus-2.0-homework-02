#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <algorithm>
#include <array>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using ip_addr_str_t = std::vector<std::string>;
using ip_addr_num_t = std::array<uint8_t, 4>;
using ip_pool_t = std::vector<ip_addr_str_t>;
using index_t = uint32_t;

ip_addr_str_t split(const std::string &str, char d)
{
    ip_addr_str_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void read_from_file(const std::string& file_name, ip_pool_t& ip_pool)
{
    std::ifstream file_stream(file_name);

    for(std::string line; std::getline(file_stream, line);)
    {
        ip_addr_str_t v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
}

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

bool check_ip(const uint8_t*)
{
    return true;
}

template <typename ... Types>
bool check_ip(const uint8_t* ip_array, uint8_t val, Types ... args)
{
    return (*ip_array == val) && check_ip(ip_array + 1, args...);
}

int main()
{
    try
    {
        std::string file_name("/media/glaugrub/Data/git/otus-homeworks/otus-2.0-homework-02/ip_filter.tsv");

        // 1. Read IPs from source
        ip_pool_t ip_pool_str;
        read_from_file(file_name, ip_pool_str);

        // 2. Convert literal IPs to numerical indexes for easy sorting
        std::vector<index_t> ip_index_pool;
        ip_index_pool.reserve(ip_pool_str.size());

        ip_addr_num_t ip_num = {};

        for (auto& ip_str : ip_pool_str)
        {
            get_numerical_ip(ip_str, ip_num);
            ip_index_pool.push_back(generate_index(ip_num));
        }

        // 3. Sort indexes
        std::sort(ip_index_pool.begin(), ip_index_pool.end());

        // 4. Convert indexes to numerical IPs
        std::vector<ip_addr_num_t> ip_pool_num;
        ip_pool_num.reserve(ip_pool_str.size());

        for (auto ip_idx : ip_index_pool)
        {
            generate_ip(ip_idx, ip_num);
            ip_pool_num.push_back(ip_num);
        }

        // 5. Print all IPs reverse order
        for (auto ip = ip_pool_num.crbegin(); ip != ip_pool_num.crend(); ip++)
        {
            print_ip(*ip);
        }

        // 6. Print IPs starting from 1
        for (auto ip = ip_pool_num.crbegin(); ip != ip_pool_num.crend(); ip++)
        {
            if (check_ip(&((*ip).at(0)), 1))
            {
                print_ip(*ip);
            }
        }

        // 7. Print IPs starting from 46, 70
        for (auto ip = ip_pool_num.crbegin(); ip != ip_pool_num.crend(); ip++)
        {
            if (check_ip(&((*ip).at(0)), 46, 70))
            {
                print_ip(*ip);
            }
        }

        // 8. Print IPs having 46
        const uint8_t val_to_check = 46;

        auto test_ip = [val_to_check](const ip_addr_num_t& ip) -> bool {
            return std::find(ip.cbegin(), ip.cend(), val_to_check) != ip.cend();
        };

        auto ip = ip_pool_num.rbegin();

        while ((ip = std::find_if(ip, ip_pool_num.rend(), test_ip)) != ip_pool_num.rend())
        {
            print_ip(*ip++);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
