# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /cygdrive/c/Users/Georgii/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Georgii/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/Science/kmu2021/Deltas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug

# Include any dependencies generated for this target.
include Sample/CMakeFiles/SampleExe.dir/depend.make

# Include the progress variables for this target.
include Sample/CMakeFiles/SampleExe.dir/progress.make

# Include the compile flags for this target's objects.
include Sample/CMakeFiles/SampleExe.dir/flags.make

Sample/CMakeFiles/SampleExe.dir/main.cpp.o: Sample/CMakeFiles/SampleExe.dir/flags.make
Sample/CMakeFiles/SampleExe.dir/main.cpp.o: ../Sample/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Sample/CMakeFiles/SampleExe.dir/main.cpp.o"
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SampleExe.dir/main.cpp.o -c /cygdrive/d/Science/kmu2021/Deltas/Sample/main.cpp

Sample/CMakeFiles/SampleExe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SampleExe.dir/main.cpp.i"
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/d/Science/kmu2021/Deltas/Sample/main.cpp > CMakeFiles/SampleExe.dir/main.cpp.i

Sample/CMakeFiles/SampleExe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SampleExe.dir/main.cpp.s"
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/d/Science/kmu2021/Deltas/Sample/main.cpp -o CMakeFiles/SampleExe.dir/main.cpp.s

# Object files for target SampleExe
SampleExe_OBJECTS = \
"CMakeFiles/SampleExe.dir/main.cpp.o"

# External object files for target SampleExe
SampleExe_EXTERNAL_OBJECTS =

Sample/SampleExe.exe: Sample/CMakeFiles/SampleExe.dir/main.cpp.o
Sample/SampleExe.exe: Sample/CMakeFiles/SampleExe.dir/build.make
Sample/SampleExe.exe: Library/libDeltaLibrary.a
Sample/SampleExe.exe: Sample/CMakeFiles/SampleExe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SampleExe.exe"
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SampleExe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Sample/CMakeFiles/SampleExe.dir/build: Sample/SampleExe.exe

.PHONY : Sample/CMakeFiles/SampleExe.dir/build

Sample/CMakeFiles/SampleExe.dir/clean:
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample && $(CMAKE_COMMAND) -P CMakeFiles/SampleExe.dir/cmake_clean.cmake
.PHONY : Sample/CMakeFiles/SampleExe.dir/clean

Sample/CMakeFiles/SampleExe.dir/depend:
	cd /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/Science/kmu2021/Deltas /cygdrive/d/Science/kmu2021/Deltas/Sample /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample /cygdrive/d/Science/kmu2021/Deltas/cmake-build-debug/Sample/CMakeFiles/SampleExe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Sample/CMakeFiles/SampleExe.dir/depend
