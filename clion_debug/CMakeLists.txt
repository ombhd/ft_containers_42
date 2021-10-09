cmake_minimum_required(VERSION 3.15)
project(clion_debug)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(clion_debug
        binary_search_tree.hpp
        map.hpp
        map_tests.cpp
        pair.hpp
        utils.hpp)
