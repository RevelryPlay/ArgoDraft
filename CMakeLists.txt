cmake_minimum_required(VERSION 3.28)
project(ArgoDraft)

set(CMAKE_CXX_STANDARD 23 LANGUAGES CXX C)

add_library(
        ArgoDraft STATIC

        ArgoDraft.cpp
        Networking.cpp
        FileSystem.cpp
)
