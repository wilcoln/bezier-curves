# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/wilcoln/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wilcoln/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wilcoln/CLionProjects/projetMath

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wilcoln/CLionProjects/projetMath/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/projetMath.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/projetMath.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projetMath.dir/flags.make

CMakeFiles/projetMath.dir/main.cpp.o: CMakeFiles/projetMath.dir/flags.make
CMakeFiles/projetMath.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wilcoln/CLionProjects/projetMath/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/projetMath.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/projetMath.dir/main.cpp.o -c /home/wilcoln/CLionProjects/projetMath/main.cpp

CMakeFiles/projetMath.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/projetMath.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wilcoln/CLionProjects/projetMath/main.cpp > CMakeFiles/projetMath.dir/main.cpp.i

CMakeFiles/projetMath.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/projetMath.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wilcoln/CLionProjects/projetMath/main.cpp -o CMakeFiles/projetMath.dir/main.cpp.s

# Object files for target projetMath
projetMath_OBJECTS = \
"CMakeFiles/projetMath.dir/main.cpp.o"

# External object files for target projetMath
projetMath_EXTERNAL_OBJECTS =

projetMath: CMakeFiles/projetMath.dir/main.cpp.o
projetMath: CMakeFiles/projetMath.dir/build.make
projetMath: CMakeFiles/projetMath.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wilcoln/CLionProjects/projetMath/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable projetMath"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projetMath.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projetMath.dir/build: projetMath

.PHONY : CMakeFiles/projetMath.dir/build

CMakeFiles/projetMath.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/projetMath.dir/cmake_clean.cmake
.PHONY : CMakeFiles/projetMath.dir/clean

CMakeFiles/projetMath.dir/depend:
	cd /home/wilcoln/CLionProjects/projetMath/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wilcoln/CLionProjects/projetMath /home/wilcoln/CLionProjects/projetMath /home/wilcoln/CLionProjects/projetMath/cmake-build-debug /home/wilcoln/CLionProjects/projetMath/cmake-build-debug /home/wilcoln/CLionProjects/projetMath/cmake-build-debug/CMakeFiles/projetMath.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projetMath.dir/depend

