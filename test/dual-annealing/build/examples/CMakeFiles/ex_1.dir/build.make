# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /test/dual-annealing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /test/dual-annealing/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/ex_1.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/ex_1.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/ex_1.dir/flags.make

examples/CMakeFiles/ex_1.dir/ex_1.cpp.o: examples/CMakeFiles/ex_1.dir/flags.make
examples/CMakeFiles/ex_1.dir/ex_1.cpp.o: ../examples/ex_1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/test/dual-annealing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/ex_1.dir/ex_1.cpp.o"
	cd /test/dual-annealing/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex_1.dir/ex_1.cpp.o -c /test/dual-annealing/examples/ex_1.cpp

examples/CMakeFiles/ex_1.dir/ex_1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex_1.dir/ex_1.cpp.i"
	cd /test/dual-annealing/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /test/dual-annealing/examples/ex_1.cpp > CMakeFiles/ex_1.dir/ex_1.cpp.i

examples/CMakeFiles/ex_1.dir/ex_1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex_1.dir/ex_1.cpp.s"
	cd /test/dual-annealing/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /test/dual-annealing/examples/ex_1.cpp -o CMakeFiles/ex_1.dir/ex_1.cpp.s

# Object files for target ex_1
ex_1_OBJECTS = \
"CMakeFiles/ex_1.dir/ex_1.cpp.o"

# External object files for target ex_1
ex_1_EXTERNAL_OBJECTS =

examples/ex_1: examples/CMakeFiles/ex_1.dir/ex_1.cpp.o
examples/ex_1: examples/CMakeFiles/ex_1.dir/build.make
examples/ex_1: examples/CMakeFiles/ex_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/test/dual-annealing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex_1"
	cd /test/dual-annealing/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/ex_1.dir/build: examples/ex_1

.PHONY : examples/CMakeFiles/ex_1.dir/build

examples/CMakeFiles/ex_1.dir/clean:
	cd /test/dual-annealing/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/ex_1.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/ex_1.dir/clean

examples/CMakeFiles/ex_1.dir/depend:
	cd /test/dual-annealing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /test/dual-annealing /test/dual-annealing/examples /test/dual-annealing/build /test/dual-annealing/build/examples /test/dual-annealing/build/examples/CMakeFiles/ex_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/ex_1.dir/depend
