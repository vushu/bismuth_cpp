# CMake generated Testfile for 
# Source directory: /home/dhv/coding/cpp/bismuth_cpp/bismuth
# Build directory: /home/dhv/coding/cpp/bismuth_cpp/game/bismuth
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "/home/dhv/coding/cpp/bismuth_cpp/game/bin/bismuth_test")
set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "/home/dhv/coding/cpp/bismuth_cpp/bismuth/CMakeLists.txt;124;add_test;/home/dhv/coding/cpp/bismuth_cpp/bismuth/CMakeLists.txt;0;")
subdirs("externals/glad")
subdirs("externals/miniaudio")
subdirs("externals/box2d")
subdirs("externals/imgui")
subdirs("externals/nanovg")
subdirs("externals/tmxlite")
subdirs("tests")
