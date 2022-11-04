cmake_minimum_required(VERSION 3.22)
project(formal_prac)

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(formal_prac main.cpp)
