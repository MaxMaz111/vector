cmake_minimum_required(VERSION 3.13)

project(vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_vector src/test.cpp)

target_include_directories(test_vector PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/util)

enable_testing()
