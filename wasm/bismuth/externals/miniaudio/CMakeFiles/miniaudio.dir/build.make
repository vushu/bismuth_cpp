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
CMAKE_SOURCE_DIR = /home/vushu/coding/cpp/somethingcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vushu/coding/cpp/somethingcpp/wasm

# Include any dependencies generated for this target.
include bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/depend.make

# Include the progress variables for this target.
include bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/progress.make

# Include the compile flags for this target's objects.
include bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/flags.make

bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.o: bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/flags.make
bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.o: bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/includes_C.rsp
bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.o: ../bismuth/externals/miniaudio/src/miniaudio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vushu/coding/cpp/somethingcpp/wasm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.o"
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && /home/vushu/coding/repos/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniaudio.dir/src/miniaudio.c.o   -c /home/vushu/coding/cpp/somethingcpp/bismuth/externals/miniaudio/src/miniaudio.c

bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniaudio.dir/src/miniaudio.c.i"
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && /home/vushu/coding/repos/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vushu/coding/cpp/somethingcpp/bismuth/externals/miniaudio/src/miniaudio.c > CMakeFiles/miniaudio.dir/src/miniaudio.c.i

bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniaudio.dir/src/miniaudio.c.s"
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && /home/vushu/coding/repos/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vushu/coding/cpp/somethingcpp/bismuth/externals/miniaudio/src/miniaudio.c -o CMakeFiles/miniaudio.dir/src/miniaudio.c.s

# Object files for target miniaudio
miniaudio_OBJECTS = \
"CMakeFiles/miniaudio.dir/src/miniaudio.c.o"

# External object files for target miniaudio
miniaudio_EXTERNAL_OBJECTS =

bismuth/externals/miniaudio/libminiaudio.a: bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/src/miniaudio.c.o
bismuth/externals/miniaudio/libminiaudio.a: bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/build.make
bismuth/externals/miniaudio/libminiaudio.a: bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vushu/coding/cpp/somethingcpp/wasm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libminiaudio.a"
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && $(CMAKE_COMMAND) -P CMakeFiles/miniaudio.dir/cmake_clean_target.cmake
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/miniaudio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/build: bismuth/externals/miniaudio/libminiaudio.a

.PHONY : bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/build

bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/clean:
	cd /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio && $(CMAKE_COMMAND) -P CMakeFiles/miniaudio.dir/cmake_clean.cmake
.PHONY : bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/clean

bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/depend:
	cd /home/vushu/coding/cpp/somethingcpp/wasm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vushu/coding/cpp/somethingcpp /home/vushu/coding/cpp/somethingcpp/bismuth/externals/miniaudio /home/vushu/coding/cpp/somethingcpp/wasm /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio /home/vushu/coding/cpp/somethingcpp/wasm/bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bismuth/externals/miniaudio/CMakeFiles/miniaudio.dir/depend

