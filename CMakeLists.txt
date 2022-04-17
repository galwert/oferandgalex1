cmake_minimum_required(VERSION 3.16)
project(skeleton_smash)

set(CMAKE_CXX_STANDARD 14)

add_executable(skeleton_smash signals.cpp signals.h Commands.cpp Commands.h smash.cpp)
