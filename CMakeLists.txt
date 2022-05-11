cmake_minimum_required(VERSION 3.10.2)
project(smash)

set(CMAKE_CXX_STANDARD 14)

add_executable(smash signals.cpp signals.h Commands.cpp Commands.h smash.cpp)
