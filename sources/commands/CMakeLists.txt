cmake_minimum_required(VERSION 3.16)

project(commands)

file(GLOB_RECURSE SOURCES "*.cpp" "*.c")

add_library(commands ${SOURCES})
