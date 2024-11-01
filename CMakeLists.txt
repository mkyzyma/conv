cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(NAME conv)

project(${NAME} C)

file(GLOB_RECURSE srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.c")

add_executable(${NAME} ${srcs})

target_include_directories(${NAME} PRIVATE src)
