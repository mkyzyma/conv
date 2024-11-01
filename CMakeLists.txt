cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(NAME conv)

project(${NAME} C) 

add_executable(${NAME} main.c utils.c)
