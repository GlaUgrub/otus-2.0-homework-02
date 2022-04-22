# setup project
cmake_minimum_required(VERSION 3.14)

project(otus_2_0_homework_02 VERSION 0.0.1)

# build ip_filter

add_executable(ip_filter_app ip_filter.cpp ip_tools.cpp)

set_target_properties(ip_filter_app PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

# build test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        test_gtest
        test_gtest.cpp
        ip_tools.cpp
)

target_link_libraries(
        test_gtest
        gtest_main
)

# enable test
enable_testing()
include(GoogleTest)
gtest_discover_tests(test_gtest)