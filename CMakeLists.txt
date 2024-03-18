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
        src/ConsoleMenu.tests.cpp
)

include(CTest)

if (BUILD_TESTING)
    find_package(PkgConfig)
    find_package(GTest CONFIG REQUIRED)

    add_executable(${PROJECT_NAME}-tests)

    target_sources(${PROJECT_NAME}-tests PRIVATE
            src/ConsoleMenu.cpp include/ConsoleMenu.hpp
            src/ConsoleMenu.tests.cpp
    )

    target_include_directories(${PROJECT_NAME}-tests PUBLIC ${PROJECT_BINARY_DIR})

    enable_testing()

    target_link_libraries(${PROJECT_NAME}-tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    target_compile_options(${PROJECT_NAME}-tests PRIVATE ${GTEST_CFLAGS})

    include(GoogleTest)

    gtest_discover_tests(${PROJECT_NAME}-tests)
endif ()
