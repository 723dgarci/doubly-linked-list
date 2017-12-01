cmake_minimum_required(VERSION 3.8)
project(Assignment2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test_list.cpp list.h list.hpp mystk.h)
add_executable(Assignment2 ${SOURCE_FILES})