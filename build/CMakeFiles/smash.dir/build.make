# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ofernis/oferandgalex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ofernis/oferandgalex1/build

# Include any dependencies generated for this target.
include CMakeFiles/smash.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/smash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smash.dir/flags.make

CMakeFiles/smash.dir/signals.cpp.o: CMakeFiles/smash.dir/flags.make
CMakeFiles/smash.dir/signals.cpp.o: ../signals.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofernis/oferandgalex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/smash.dir/signals.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smash.dir/signals.cpp.o -c /home/ofernis/oferandgalex1/signals.cpp

CMakeFiles/smash.dir/signals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smash.dir/signals.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofernis/oferandgalex1/signals.cpp > CMakeFiles/smash.dir/signals.cpp.i

CMakeFiles/smash.dir/signals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smash.dir/signals.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofernis/oferandgalex1/signals.cpp -o CMakeFiles/smash.dir/signals.cpp.s

CMakeFiles/smash.dir/signals.cpp.o.requires:

.PHONY : CMakeFiles/smash.dir/signals.cpp.o.requires

CMakeFiles/smash.dir/signals.cpp.o.provides: CMakeFiles/smash.dir/signals.cpp.o.requires
	$(MAKE) -f CMakeFiles/smash.dir/build.make CMakeFiles/smash.dir/signals.cpp.o.provides.build
.PHONY : CMakeFiles/smash.dir/signals.cpp.o.provides

CMakeFiles/smash.dir/signals.cpp.o.provides.build: CMakeFiles/smash.dir/signals.cpp.o


CMakeFiles/smash.dir/Commands.cpp.o: CMakeFiles/smash.dir/flags.make
CMakeFiles/smash.dir/Commands.cpp.o: ../Commands.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofernis/oferandgalex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/smash.dir/Commands.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smash.dir/Commands.cpp.o -c /home/ofernis/oferandgalex1/Commands.cpp

CMakeFiles/smash.dir/Commands.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smash.dir/Commands.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofernis/oferandgalex1/Commands.cpp > CMakeFiles/smash.dir/Commands.cpp.i

CMakeFiles/smash.dir/Commands.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smash.dir/Commands.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofernis/oferandgalex1/Commands.cpp -o CMakeFiles/smash.dir/Commands.cpp.s

CMakeFiles/smash.dir/Commands.cpp.o.requires:

.PHONY : CMakeFiles/smash.dir/Commands.cpp.o.requires

CMakeFiles/smash.dir/Commands.cpp.o.provides: CMakeFiles/smash.dir/Commands.cpp.o.requires
	$(MAKE) -f CMakeFiles/smash.dir/build.make CMakeFiles/smash.dir/Commands.cpp.o.provides.build
.PHONY : CMakeFiles/smash.dir/Commands.cpp.o.provides

CMakeFiles/smash.dir/Commands.cpp.o.provides.build: CMakeFiles/smash.dir/Commands.cpp.o


CMakeFiles/smash.dir/smash.cpp.o: CMakeFiles/smash.dir/flags.make
CMakeFiles/smash.dir/smash.cpp.o: ../smash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofernis/oferandgalex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/smash.dir/smash.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smash.dir/smash.cpp.o -c /home/ofernis/oferandgalex1/smash.cpp

CMakeFiles/smash.dir/smash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smash.dir/smash.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofernis/oferandgalex1/smash.cpp > CMakeFiles/smash.dir/smash.cpp.i

CMakeFiles/smash.dir/smash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smash.dir/smash.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofernis/oferandgalex1/smash.cpp -o CMakeFiles/smash.dir/smash.cpp.s

CMakeFiles/smash.dir/smash.cpp.o.requires:

.PHONY : CMakeFiles/smash.dir/smash.cpp.o.requires

CMakeFiles/smash.dir/smash.cpp.o.provides: CMakeFiles/smash.dir/smash.cpp.o.requires
	$(MAKE) -f CMakeFiles/smash.dir/build.make CMakeFiles/smash.dir/smash.cpp.o.provides.build
.PHONY : CMakeFiles/smash.dir/smash.cpp.o.provides

CMakeFiles/smash.dir/smash.cpp.o.provides.build: CMakeFiles/smash.dir/smash.cpp.o


# Object files for target smash
smash_OBJECTS = \
"CMakeFiles/smash.dir/signals.cpp.o" \
"CMakeFiles/smash.dir/Commands.cpp.o" \
"CMakeFiles/smash.dir/smash.cpp.o"

# External object files for target smash
smash_EXTERNAL_OBJECTS =

smash: CMakeFiles/smash.dir/signals.cpp.o
smash: CMakeFiles/smash.dir/Commands.cpp.o
smash: CMakeFiles/smash.dir/smash.cpp.o
smash: CMakeFiles/smash.dir/build.make
smash: CMakeFiles/smash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ofernis/oferandgalex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable smash"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smash.dir/build: smash

.PHONY : CMakeFiles/smash.dir/build

CMakeFiles/smash.dir/requires: CMakeFiles/smash.dir/signals.cpp.o.requires
CMakeFiles/smash.dir/requires: CMakeFiles/smash.dir/Commands.cpp.o.requires
CMakeFiles/smash.dir/requires: CMakeFiles/smash.dir/smash.cpp.o.requires

.PHONY : CMakeFiles/smash.dir/requires

CMakeFiles/smash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smash.dir/clean

CMakeFiles/smash.dir/depend:
	cd /home/ofernis/oferandgalex1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ofernis/oferandgalex1 /home/ofernis/oferandgalex1 /home/ofernis/oferandgalex1/build /home/ofernis/oferandgalex1/build /home/ofernis/oferandgalex1/build/CMakeFiles/smash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smash.dir/depend

