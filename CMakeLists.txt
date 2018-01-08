cmake_minimum_required (VERSION 2.8.4)
project (fsm)
# The version number.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

include_directories("inc" "tests")
 
# add the library
add_library(fsm STATIC src/fsm.cc)


##############
# Google Test
##############

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")


##############
# Unit Tests
##############
add_executable(run_unit_tests tests/main.cpp src/fsm.cc tests/simple_fsm.cc)

# Standard linking to gtest stuff.
target_link_libraries(run_unit_tests gtest gtest_main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable run_unit_tests to see those specific tests.
add_test(NAME that-test-I-made COMMAND run_unit_tests)

