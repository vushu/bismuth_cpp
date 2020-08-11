# CMake generated Testfile for 
# Source directory: /home/vushu/coding/cpp/somethingcpp/bismuth
# Build directory: /home/vushu/coding/cpp/somethingcpp/native/bismuth
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "/home/vushu/coding/cpp/somethingcpp/native/bin/bismuth_test")
set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "/home/vushu/coding/cpp/somethingcpp/bismuth/CMakeLists.txt;76;add_test;/home/vushu/coding/cpp/somethingcpp/bismuth/CMakeLists.txt;0;")
subdirs("externals/glad")
subdirs("tests")
