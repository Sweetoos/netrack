cmake_minimum_required(VERSION 3.29)
project(netrack)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

if(UNIX AND NOT WIN32)
    message(STATUS "Configuring libpcap for UNIX")
    FetchContent_Declare(
        libpcap
        GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
        GIT_TAG        libpcap-1.10.4
    )
    FetchContent_MakeAvailable(libpcap)
    set(PCAP_TARGET pcap)
elseif(WIN32)
    message(FATAL_ERROR "For now this project doesn't work on Windows")
else()
    message(FATAL_ERROR "This OS is not supported")
endif()

add_library(netrack_lib STATIC
    src/RingBuffer.cpp
)
target_compile_options(netrack_lib PRIVATE -Wall -Wextra -Wpedantic -g)

target_include_directories(netrack_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/inc"
)


add_executable(netrack
    src/netrack.cpp
)

target_link_libraries(netrack PRIVATE
    netrack_lib
    ${PCAP_TARGET}
)

option(BUILD_TESTING "Build the tests" ON)

if(BUILD_TESTING)
    enable_testing()

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "v1.14.0"
    )
    set(INSTALL_GTEST OFF)
    set(BUILD_GMOCK OFF)
    FetchContent_MakeAvailable(googletest)

    add_executable(testing
        tests/ring_buffer.cpp
    )

    target_link_libraries(testing PRIVATE
        GTest::gtest_main
        netrack_lib
    )

    include(GoogleTest)
    gtest_discover_tests(testing)

endif()
