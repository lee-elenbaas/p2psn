# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lee/projects/math

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lee/projects/math/build

# Include any dependencies generated for this target.
include CMakeFiles/mathTests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mathTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mathTests.dir/flags.make

CMakeFiles/mathTests.dir/modulu/mod.cpp.o: CMakeFiles/mathTests.dir/flags.make
CMakeFiles/mathTests.dir/modulu/mod.cpp.o: ../modulu/mod.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lee/projects/math/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mathTests.dir/modulu/mod.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mathTests.dir/modulu/mod.cpp.o -c /home/lee/projects/math/modulu/mod.cpp

CMakeFiles/mathTests.dir/modulu/mod.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mathTests.dir/modulu/mod.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lee/projects/math/modulu/mod.cpp > CMakeFiles/mathTests.dir/modulu/mod.cpp.i

CMakeFiles/mathTests.dir/modulu/mod.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mathTests.dir/modulu/mod.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lee/projects/math/modulu/mod.cpp -o CMakeFiles/mathTests.dir/modulu/mod.cpp.s

CMakeFiles/mathTests.dir/modulu/mod.cpp.o.requires:
.PHONY : CMakeFiles/mathTests.dir/modulu/mod.cpp.o.requires

CMakeFiles/mathTests.dir/modulu/mod.cpp.o.provides: CMakeFiles/mathTests.dir/modulu/mod.cpp.o.requires
	$(MAKE) -f CMakeFiles/mathTests.dir/build.make CMakeFiles/mathTests.dir/modulu/mod.cpp.o.provides.build
.PHONY : CMakeFiles/mathTests.dir/modulu/mod.cpp.o.provides

CMakeFiles/mathTests.dir/modulu/mod.cpp.o.provides.build: CMakeFiles/mathTests.dir/modulu/mod.cpp.o

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o: CMakeFiles/mathTests.dir/flags.make
CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o: ../polynomial/full_polynomial_stream_traits.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lee/projects/math/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o -c /home/lee/projects/math/polynomial/full_polynomial_stream_traits.cpp

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lee/projects/math/polynomial/full_polynomial_stream_traits.cpp > CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.i

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lee/projects/math/polynomial/full_polynomial_stream_traits.cpp -o CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.s

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.requires:
.PHONY : CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.requires

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.provides: CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.requires
	$(MAKE) -f CMakeFiles/mathTests.dir/build.make CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.provides.build
.PHONY : CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.provides

CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.provides.build: CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o

CMakeFiles/mathTests.dir/main.cpp.o: CMakeFiles/mathTests.dir/flags.make
CMakeFiles/mathTests.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lee/projects/math/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mathTests.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mathTests.dir/main.cpp.o -c /home/lee/projects/math/main.cpp

CMakeFiles/mathTests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mathTests.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lee/projects/math/main.cpp > CMakeFiles/mathTests.dir/main.cpp.i

CMakeFiles/mathTests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mathTests.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lee/projects/math/main.cpp -o CMakeFiles/mathTests.dir/main.cpp.s

CMakeFiles/mathTests.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/mathTests.dir/main.cpp.o.requires

CMakeFiles/mathTests.dir/main.cpp.o.provides: CMakeFiles/mathTests.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mathTests.dir/build.make CMakeFiles/mathTests.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mathTests.dir/main.cpp.o.provides

CMakeFiles/mathTests.dir/main.cpp.o.provides.build: CMakeFiles/mathTests.dir/main.cpp.o

# Object files for target mathTests
mathTests_OBJECTS = \
"CMakeFiles/mathTests.dir/modulu/mod.cpp.o" \
"CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o" \
"CMakeFiles/mathTests.dir/main.cpp.o"

# External object files for target mathTests
mathTests_EXTERNAL_OBJECTS =

mathTests: CMakeFiles/mathTests.dir/modulu/mod.cpp.o
mathTests: CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o
mathTests: CMakeFiles/mathTests.dir/main.cpp.o
mathTests: libtests.a
mathTests: CMakeFiles/mathTests.dir/build.make
mathTests: CMakeFiles/mathTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mathTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mathTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mathTests.dir/build: mathTests
.PHONY : CMakeFiles/mathTests.dir/build

CMakeFiles/mathTests.dir/requires: CMakeFiles/mathTests.dir/modulu/mod.cpp.o.requires
CMakeFiles/mathTests.dir/requires: CMakeFiles/mathTests.dir/polynomial/full_polynomial_stream_traits.cpp.o.requires
CMakeFiles/mathTests.dir/requires: CMakeFiles/mathTests.dir/main.cpp.o.requires
.PHONY : CMakeFiles/mathTests.dir/requires

CMakeFiles/mathTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mathTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mathTests.dir/clean

CMakeFiles/mathTests.dir/depend:
	cd /home/lee/projects/math/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lee/projects/math /home/lee/projects/math /home/lee/projects/math/build /home/lee/projects/math/build /home/lee/projects/math/build/CMakeFiles/mathTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mathTests.dir/depend
