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

FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG "v1.14.0")
set(GTEST_INSTALL
    OFF
    CACHE BOOL "Disable gtest install target")
set(BUILD_GMOCK
    OFF
    CACHE BOOL "Disable building gmock if not needed")
FetchContent_MakeAvailable(googletest)

add_executable(netrack 
    src/netrack.cpp
    src/RingBuffer.cpp
)

target_include_directories(netrack PRIVATE "${PROJECT_SOURCE_DIR}/inc")     
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")

target_link_libraries(netrack PRIVATE gtest_main)
target_link_libraries(netrack PRIVATE ${PCAP_TARGET})

