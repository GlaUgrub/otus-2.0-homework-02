#pragma once

#include <string>
#include <vector>
#include <array>
#include <stdint.h>

using ip_addr_str_t = std::vector<std::string>;
using ip_addr_num_t = std::array<uint8_t, 4>;
using ip_pool_t = std::vector<ip_addr_str_t>;
using index_t = uint32_t;

void get_numerical_ip(const ip_addr_str_t&, ip_addr_num_t&);

index_t generate_index(const ip_addr_num_t&);

void generate_ip(index_t, ip_addr_num_t&);

void print_ip(const ip_addr_num_t& ip);