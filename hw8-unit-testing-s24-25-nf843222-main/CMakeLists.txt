# Specify the minimum version of CMake.
# You should use the latest version possible since there are
# ton of legacy CMake functions.
#
# In this case, we pin it to version 3.16 since GitHub Codespace
# has 3.16.3 by default.
cmake_minimum_required(VERSION 3.16)

# Name the project `UnitTestingHomework`.
project(UnitTestingHomework LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# Dependencies declaration and fetching.
#
# We use FetchContent to
# fetch the dependencies we want during the configuration phase of CMake.
#
Include(FetchContent)

FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.1.1
)


FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)


#
# STEP 4 - TASK 1
#
# HINT: Use FetchContent_Declare to get source code of Catch2 v3.7.1
#       from https://github.com/catchorg/Catch2.git
#
# YOUR_ANSWER


#
# # STEP 4 - TASK 2
#
# HINT: Modify the FetchContent_MakeAvailable to also make Catch2 available.
#
# YOUR_ANSWER
FetchContent_MakeAvailable(cxxopts Catch2)


#
# Define library.
#
add_library(lib college.cpp college.hpp course.cpp course.hpp)
# See https://stackoverflow.com/questions/41814426/cmake-cant-find-header-files
target_include_directories(lib PUBLIC ./)
target_compile_features(lib PUBLIC cxx_std_17)


# Define an executable name and its source file.
# This should be straightforward, an executable file name
# college-app is compiled from main.cpp file.
add_executable(college-app main.cpp)

# We then link said executable to the library named lib and cxxopts.
target_link_libraries(college-app lib cxxopts)

#
# STEP 5 - TASK 1 AND TASK 2
#
# HINT: Use add_executable to add tests executable with test_college.cpp
#       Then use target_link_libraries to link this tests target with necessary libraries.
#
# YOUR_ANSWER

add_executable(tests test_college.cpp)
target_link_libraries(tests lib Catch2::Catch2WithMain)
