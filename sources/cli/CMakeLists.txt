cmake_minimum_required(VERSION 3.16)
project(cli)

file(GLOB_RECURSE SOURCES "*.cpp" "*.c")

add_library(cli ${SOURCES})