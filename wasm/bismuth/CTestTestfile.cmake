# CMake generated Testfile for 
# Source directory: /home/vushu/coding/cpp/somethingcpp/bismuth
# Build directory: /home/vushu/coding/cpp/somethingcpp/wasm/bismuth
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "\"/home/vushu/coding/repos/emsdk/node/12.18.1_64bit/bin/node\"" "/home/vushu/coding/cpp/somethingcpp/wasm/bin/bismuth_test.js")
set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "/home/vushu/coding/cpp/somethingcpp/bismuth/CMakeLists.txt;90;add_test;/home/vushu/coding/cpp/somethingcpp/bismuth/CMakeLists.txt;0;")
subdirs("externals/glad")
subdirs("externals/miniaudio")
subdirs("externals/box2d")
subdirs("tests")
