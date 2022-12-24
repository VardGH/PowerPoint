cmake_minimum_required(VERSION 3.16)

project(common)

file(GLOB_RECURSE SOURCES "*.cpp" "*.c")

add_library(common ${SOURCES})
