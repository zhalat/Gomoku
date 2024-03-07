cmake_minimum_required(VERSION 3.13)

project(gomokuBackendCLI
        VERSION 1.0.1
        DESCRIPTION "Gomoku algorithm implementation from scratch"
        LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Missing CMAKE_BUILD_TYPE, set to Debug or Release")
endif()

find_package(Boost 1.74 REQUIRED COMPONENTS program_options filesystem regex)
find_package(Threads)

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fstack-usage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(core)
get_target_property(gomokuAlgo_SRC_PATH gomokuAlgo SOURCE_DIR)
get_target_property(gomokuAlgo_INCLUDE_DIR gomokuAlgo INTERFACE_INCLUDE_DIRECTORIES)

add_executable( gomokuBackendCLI
        main.cpp
        GomokuGameCLI.cpp
        GomokuGameCLI.h
)

target_include_directories(gomokuBackendCLI
     PRIVATE "${gomokuAlgo_INCLUDE_DIR}"
)

target_link_libraries( gomokuBackendCLI PRIVATE
        gomokuAlgo
        pthread
        Boost::program_options
        Boost::filesystem
        Boost::regex
)

target_link_options(gomokuAlgo PRIVATE
        -Wl,-Map,output.map
        -Wl,--print-memory-usage
        -Wl,--gc-sections
        -lc
)

#Google tests
include(cmake/google-test.cmake)