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
CMAKE_BINARY_DIR = /home/vushu/coding/cpp/somethingcpp/native

# Include any dependencies generated for this target.
include test/CMakeFiles/TestGame.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/TestGame.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/TestGame.dir/flags.make

test/CMakeFiles/TestGame.dir/src/game.cpp.o: test/CMakeFiles/TestGame.dir/flags.make
test/CMakeFiles/TestGame.dir/src/game.cpp.o: ../test/src/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vushu/coding/cpp/somethingcpp/native/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/TestGame.dir/src/game.cpp.o"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestGame.dir/src/game.cpp.o -c /home/vushu/coding/cpp/somethingcpp/test/src/game.cpp

test/CMakeFiles/TestGame.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestGame.dir/src/game.cpp.i"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vushu/coding/cpp/somethingcpp/test/src/game.cpp > CMakeFiles/TestGame.dir/src/game.cpp.i

test/CMakeFiles/TestGame.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestGame.dir/src/game.cpp.s"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vushu/coding/cpp/somethingcpp/test/src/game.cpp -o CMakeFiles/TestGame.dir/src/game.cpp.s

test/CMakeFiles/TestGame.dir/src/main.cpp.o: test/CMakeFiles/TestGame.dir/flags.make
test/CMakeFiles/TestGame.dir/src/main.cpp.o: ../test/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vushu/coding/cpp/somethingcpp/native/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/TestGame.dir/src/main.cpp.o"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestGame.dir/src/main.cpp.o -c /home/vushu/coding/cpp/somethingcpp/test/src/main.cpp

test/CMakeFiles/TestGame.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestGame.dir/src/main.cpp.i"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vushu/coding/cpp/somethingcpp/test/src/main.cpp > CMakeFiles/TestGame.dir/src/main.cpp.i

test/CMakeFiles/TestGame.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestGame.dir/src/main.cpp.s"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vushu/coding/cpp/somethingcpp/test/src/main.cpp -o CMakeFiles/TestGame.dir/src/main.cpp.s

# Object files for target TestGame
TestGame_OBJECTS = \
"CMakeFiles/TestGame.dir/src/game.cpp.o" \
"CMakeFiles/TestGame.dir/src/main.cpp.o"

# External object files for target TestGame
TestGame_EXTERNAL_OBJECTS =

bin/TestGame: test/CMakeFiles/TestGame.dir/src/game.cpp.o
bin/TestGame: test/CMakeFiles/TestGame.dir/src/main.cpp.o
bin/TestGame: test/CMakeFiles/TestGame.dir/build.make
bin/TestGame: bismuth/libbismuth.so.1.0.0
bin/TestGame: test/CMakeFiles/TestGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vushu/coding/cpp/somethingcpp/native/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/TestGame"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "symbolic link resources folder from /home/vushu/coding/cpp/somethingcpp/test/resources => /home/vushu/coding/cpp/somethingcpp/native/bin/resources"
	cd /home/vushu/coding/cpp/somethingcpp/native/test && /usr/bin/cmake -E create_symlink /home/vushu/coding/cpp/somethingcpp/test/resources /home/vushu/coding/cpp/somethingcpp/native/bin/resources
	cd /home/vushu/coding/cpp/somethingcpp/native/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/TestGame.dir/build: bin/TestGame

.PHONY : test/CMakeFiles/TestGame.dir/build

test/CMakeFiles/TestGame.dir/clean:
	cd /home/vushu/coding/cpp/somethingcpp/native/test && $(CMAKE_COMMAND) -P CMakeFiles/TestGame.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/TestGame.dir/clean

test/CMakeFiles/TestGame.dir/depend:
	cd /home/vushu/coding/cpp/somethingcpp/native && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vushu/coding/cpp/somethingcpp /home/vushu/coding/cpp/somethingcpp/test /home/vushu/coding/cpp/somethingcpp/native /home/vushu/coding/cpp/somethingcpp/native/test /home/vushu/coding/cpp/somethingcpp/native/test/CMakeFiles/TestGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/TestGame.dir/depend

