# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)

# Set <PROJNAME> to be your project name. We set CXX (C++) here as the target language.
project(<PROJNAME> VERSION 0.1.0 LANGUAGES CXX)

# If you want to see "under the hood" of CMake, uncomment this:
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(CS_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(CS_FLAGS_RELEASE "${CS_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_CPP_FLAGS ${CS_FLAGS_DEBUG})

# Add the names of your source files here
add_executable(smash smash.cpp signals.cpp Commands.cpp)

set_target_properties(smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/ofernis/oferandgalex1)
