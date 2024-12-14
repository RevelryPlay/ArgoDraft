cmake_minimum_required(VERSION 3.28)
project(ArgoDraft
        VERSION 0.0.1
        LANGUAGES CXX C
)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(
        ArgoDraft STATIC

        src/ArgoDraft.cpp include/ArgoDraft.hpp
        src/ConsoleMenu.cpp include/ConsoleMenu.hpp
        src/Networking.cpp include/Networking.hpp
        src/FileSystem.cpp include/FileSystem.hpp
        src/AroLogger.cpp include/ArgoLogger.hpp
)
