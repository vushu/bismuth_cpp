# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/cmake/743/bin/cmake

# The command to remove a file.
RM = /snap/cmake/743/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dhv/coding/cpp/bismuth_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dhv/coding/cpp/bismuth_cpp/game

# Include any dependencies generated for this target.
include bismuth/externals/glad/CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include bismuth/externals/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include bismuth/externals/glad/CMakeFiles/glad.dir/flags.make

bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.o: bismuth/externals/glad/CMakeFiles/glad.dir/flags.make
bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.o: ../bismuth/externals/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dhv/coding/cpp/bismuth_cpp/game/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.o"
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/src/glad.c.o -c /home/dhv/coding/cpp/bismuth_cpp/bismuth/externals/glad/src/glad.c

bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/src/glad.c.i"
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dhv/coding/cpp/bismuth_cpp/bismuth/externals/glad/src/glad.c > CMakeFiles/glad.dir/src/glad.c.i

bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/src/glad.c.s"
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dhv/coding/cpp/bismuth_cpp/bismuth/externals/glad/src/glad.c -o CMakeFiles/glad.dir/src/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

bismuth/externals/glad/libglad.a: bismuth/externals/glad/CMakeFiles/glad.dir/src/glad.c.o
bismuth/externals/glad/libglad.a: bismuth/externals/glad/CMakeFiles/glad.dir/build.make
bismuth/externals/glad/libglad.a: bismuth/externals/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dhv/coding/cpp/bismuth_cpp/game/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bismuth/externals/glad/CMakeFiles/glad.dir/build: bismuth/externals/glad/libglad.a

.PHONY : bismuth/externals/glad/CMakeFiles/glad.dir/build

bismuth/externals/glad/CMakeFiles/glad.dir/clean:
	cd /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : bismuth/externals/glad/CMakeFiles/glad.dir/clean

bismuth/externals/glad/CMakeFiles/glad.dir/depend:
	cd /home/dhv/coding/cpp/bismuth_cpp/game && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dhv/coding/cpp/bismuth_cpp /home/dhv/coding/cpp/bismuth_cpp/bismuth/externals/glad /home/dhv/coding/cpp/bismuth_cpp/game /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad /home/dhv/coding/cpp/bismuth_cpp/game/bismuth/externals/glad/CMakeFiles/glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bismuth/externals/glad/CMakeFiles/glad.dir/depend

