cmake_minimum_required(VERSION 3.29)
project(netrack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use a project-prefixed option name to avoid colliding with subprojects' cache vars.
option(NETRACK_ENABLE_SANITIZERS "Enable ASAN/UBSAN for debugging" ON)
# Do NOT apply sanitizer flags globally before FetchContent (breaks some subprojects like libpcap).
# Collect per-target sanitizer flags and apply them only to our targets after subprojects are configured.
set(_SANITIZE_COMPILE_FLAGS "")
set(_SANITIZE_LINK_FLAGS "")
if(NETRACK_ENABLE_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Will enable Address/Undefined sanitizers for project targets (not globally)")
    set(_SANITIZE_COMPILE_FLAGS -g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined)
    set(_SANITIZE_LINK_FLAGS -fsanitize=address,undefined)
  else()
    message(WARNING "Sanitizers requested but unsupported compiler")
  endif()
endif()

include(FetchContent)

# Prevent subprojects (libpcap) from reading generic sanitizer cache variables.
# Unset common names so libpcap won't mistake "ON" as a sanitizer name.
if(DEFINED sanitizer)
  unset(sanitizer CACHE)
endif()
if(DEFINED SANITIZER)
  unset(SANITIZER CACHE)
endif()
if(DEFINED sanitize)
  unset(sanitize CACHE)
endif()

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

add_executable(netrack
    src/netrack.cpp
    src/RingBuffer.cpp
    src/ConsumerPacket.cpp
    src/ProducerPacket.cpp
)

target_compile_options(netrack PRIVATE -Wall -Wextra -Wpedantic ${_SANITIZE_COMPILE_FLAGS})
if(_SANITIZE_LINK_FLAGS)
  target_link_options(netrack PRIVATE ${_SANITIZE_LINK_FLAGS})
endif()

target_include_directories(netrack PRIVATE
    "${PROJECT_SOURCE_DIR}/inc"
)

target_link_libraries(netrack PRIVATE 
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
    set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install target")
    set(BUILD_GMOCK OFF CACHE BOOL "Disable building gmock if not needed")
    FetchContent_MakeAvailable(googletest)

    add_executable(testing
        tests/ring_buffer.cpp
        src/RingBuffer.cpp
        src/ConsumerPacket.cpp
        src/ProducerPacket.cpp
    )

    target_compile_options(testing PRIVATE -Wall -Wextra -Wpedantic ${_SANITIZE_COMPILE_FLAGS})
    if(_SANITIZE_LINK_FLAGS)
      target_link_options(testing PRIVATE ${_SANITIZE_LINK_FLAGS})
    endif()
     target_include_directories(testing PRIVATE
         "${PROJECT_SOURCE_DIR}/inc"
     )

     target_link_libraries(testing PRIVATE
         GTest::gtest_main
         ${PCAP_TARGET}
     )

     include(GoogleTest)
     gtest_discover_tests(testing)

endif()
