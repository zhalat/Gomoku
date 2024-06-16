cmake_minimum_required(VERSION 3.13)

project(gomokuBackend
        VERSION 1.0.1
        DESCRIPTION "Gomoku algorithm implementation from scratch"
        LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Missing CMAKE_BUILD_TYPE, set to Debug or Release")
endif()


include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fstack-usage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build core library
add_subdirectory(core)

#build UT
include(cmake/google-test.cmake)