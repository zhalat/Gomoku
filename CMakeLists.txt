cmake_minimum_required(VERSION 3.13)

project(Gomoku 
        VERSION 1.0
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

add_subdirectory(src)

#Google tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
if(GTEST_FOUND)
	enable_testing()
	add_subdirectory(ci/UT)
endif()

#Clang format
#find_package(Python3)
#if(Python3_Interpreter_FOUND)
#    add_custom_target(format_sources ALL
#        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/code_format/clang-format.py --path=${CMAKE_SOURCE_DIR} --clang_ignore ${CMAKE_SOURCE_DIR}/scripts/code_format/.clangignore
#        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#        COMMENT "Format source code using clang-format tool"
#    )
#endif()