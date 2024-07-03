# CMake generated Testfile for 
# Source directory: C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test
# Build directory: C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxxbuild/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(runner "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxxbuild/test/Debug/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;12;add_test;C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(runner "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxxbuild/test/Release/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;12;add_test;C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(runner "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxxbuild/test/MinSizeRel/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;12;add_test;C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(runner "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxxbuild/test/RelWithDebInfo/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;12;add_test;C:/Users/UA/Documents/projects/libraryManagementSystem2/libpqxx/test/CMakeLists.txt;0;")
else()
  add_test(runner NOT_AVAILABLE)
endif()
