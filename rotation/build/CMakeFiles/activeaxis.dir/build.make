# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/pj/pj/test_eigen_or_others/rotation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pj/pj/test_eigen_or_others/rotation/build

# Include any dependencies generated for this target.
include CMakeFiles/activeaxis.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/activeaxis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/activeaxis.dir/flags.make

CMakeFiles/activeaxis.dir/activeaxis.cpp.o: CMakeFiles/activeaxis.dir/flags.make
CMakeFiles/activeaxis.dir/activeaxis.cpp.o: ../activeaxis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pj/pj/test_eigen_or_others/rotation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/activeaxis.dir/activeaxis.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/activeaxis.dir/activeaxis.cpp.o -c /home/pj/pj/test_eigen_or_others/rotation/activeaxis.cpp

CMakeFiles/activeaxis.dir/activeaxis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/activeaxis.dir/activeaxis.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pj/pj/test_eigen_or_others/rotation/activeaxis.cpp > CMakeFiles/activeaxis.dir/activeaxis.cpp.i

CMakeFiles/activeaxis.dir/activeaxis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/activeaxis.dir/activeaxis.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pj/pj/test_eigen_or_others/rotation/activeaxis.cpp -o CMakeFiles/activeaxis.dir/activeaxis.cpp.s

# Object files for target activeaxis
activeaxis_OBJECTS = \
"CMakeFiles/activeaxis.dir/activeaxis.cpp.o"

# External object files for target activeaxis
activeaxis_EXTERNAL_OBJECTS =

../bin/activeaxis: CMakeFiles/activeaxis.dir/activeaxis.cpp.o
../bin/activeaxis: CMakeFiles/activeaxis.dir/build.make
../bin/activeaxis: /usr/local/lib/libgflags.a
../bin/activeaxis: CMakeFiles/activeaxis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pj/pj/test_eigen_or_others/rotation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/activeaxis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/activeaxis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/activeaxis.dir/build: ../bin/activeaxis

.PHONY : CMakeFiles/activeaxis.dir/build

CMakeFiles/activeaxis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/activeaxis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/activeaxis.dir/clean

CMakeFiles/activeaxis.dir/depend:
	cd /home/pj/pj/test_eigen_or_others/rotation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pj/pj/test_eigen_or_others/rotation /home/pj/pj/test_eigen_or_others/rotation /home/pj/pj/test_eigen_or_others/rotation/build /home/pj/pj/test_eigen_or_others/rotation/build /home/pj/pj/test_eigen_or_others/rotation/build/CMakeFiles/activeaxis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/activeaxis.dir/depend

