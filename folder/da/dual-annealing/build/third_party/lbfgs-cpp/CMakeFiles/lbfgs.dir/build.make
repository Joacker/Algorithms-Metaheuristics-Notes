# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /f2/app/dual-annealing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /f2/app/dual-annealing/build

# Include any dependencies generated for this target.
include third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/flags.make

third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o: third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/flags.make
third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o: ../third_party/lbfgs-cpp/src/lbfgs.cpp
third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o: third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/f2/app/dual-annealing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o"
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o -MF CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o.d -o CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o -c /f2/app/dual-annealing/third_party/lbfgs-cpp/src/lbfgs.cpp

third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbfgs.dir/src/lbfgs.cpp.i"
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /f2/app/dual-annealing/third_party/lbfgs-cpp/src/lbfgs.cpp > CMakeFiles/lbfgs.dir/src/lbfgs.cpp.i

third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbfgs.dir/src/lbfgs.cpp.s"
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /f2/app/dual-annealing/third_party/lbfgs-cpp/src/lbfgs.cpp -o CMakeFiles/lbfgs.dir/src/lbfgs.cpp.s

# Object files for target lbfgs
lbfgs_OBJECTS = \
"CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o"

# External object files for target lbfgs
lbfgs_EXTERNAL_OBJECTS =

third_party/lbfgs-cpp/liblbfgs.a: third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/src/lbfgs.cpp.o
third_party/lbfgs-cpp/liblbfgs.a: third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/build.make
third_party/lbfgs-cpp/liblbfgs.a: third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/f2/app/dual-annealing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblbfgs.a"
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && $(CMAKE_COMMAND) -P CMakeFiles/lbfgs.dir/cmake_clean_target.cmake
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lbfgs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/build: third_party/lbfgs-cpp/liblbfgs.a
.PHONY : third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/build

third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/clean:
	cd /f2/app/dual-annealing/build/third_party/lbfgs-cpp && $(CMAKE_COMMAND) -P CMakeFiles/lbfgs.dir/cmake_clean.cmake
.PHONY : third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/clean

third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/depend:
	cd /f2/app/dual-annealing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /f2/app/dual-annealing /f2/app/dual-annealing/third_party/lbfgs-cpp /f2/app/dual-annealing/build /f2/app/dual-annealing/build/third_party/lbfgs-cpp /f2/app/dual-annealing/build/third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third_party/lbfgs-cpp/CMakeFiles/lbfgs.dir/depend

