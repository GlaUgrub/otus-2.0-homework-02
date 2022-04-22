# setup project
cmake_minimum_required(VERSION 3.14)

project(otus_2_0_homework_02 VERSION 0.0.1)

# build ip_filter

add_executable(ip_filter_app ip_filter.cpp)

set_target_properties(ip_filter_app PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)