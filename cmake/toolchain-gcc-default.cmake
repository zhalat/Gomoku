cmake_minimum_required(VERSION 3.13 FATAL_ERROR)


if("$ENV{DEFAULT_TOOLCHAIN_PATH}" STREQUAL "")
    message(FATAL_ERROR "env variable DEFAULT_TOOLCHAIN_PATH must be defined")
endif()

set(triplet             x86_64-linux-gnu-)
set(TOOLCHAIN_PATH      "$ENV{DEFAULT_TOOLCHAIN_PATH}")

set(CMD_GCC             "${TOOLCHAIN_PATH}/${triplet}gcc")
set(CMD_GXX             "${TOOLCHAIN_PATH}/${triplet}g++")
set(CMD_OBJDUMP         "${TOOLCHAIN_PATH}/${triplet}objdump")
set(CMD_OBJCOPY         "${TOOLCHAIN_PATH}/${triplet}objcopy")
set(CMD_SIZE            "${TOOLCHAIN_PATH}/${triplet}size")
set(CMD_LINK            "${TOOLCHAIN_PATH}/${triplet}ld")

set(CMAKE_C_COMPILER           ${CMD_GCC})
set(CMAKE_CXX_COMPILER         ${CMD_GXX})
#set(CMAKE_LIBRARY_PATH          /usr/lib/${triplet})