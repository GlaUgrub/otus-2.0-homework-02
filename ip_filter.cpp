#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "ip_tools.h"

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

void read_from_console(ip_pool_t& ip_pool)
{
    for(std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
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
        // 1. Read IPs from source
        ip_pool_t ip_pool_str;
        //std::string file_name("/media/glaugrub/Data/git/otus-homeworks/otus-2.0-homework-02/ip_filter.tsv");
        //read_from_file(file_name, ip_pool_str);
        read_from_console(ip_pool_str);

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
