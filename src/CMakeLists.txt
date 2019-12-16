cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Lib)

add_executable(src
        archiver.cpp
        archiver.hpp
        bitstring.cpp
        bitstring.hpp
        huffman.cpp
        huffman.hpp

        main_encoding.cpp
        stdc++.hpp)
