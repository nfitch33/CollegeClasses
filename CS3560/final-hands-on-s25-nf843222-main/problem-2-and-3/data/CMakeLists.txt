cmake_minimum_required(VERSION 3.16)

project(FinalExam LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

Include(FetchContent)

#
# YOUR_ANSWER: FetchContent_Declare for Catch2
#


#
# YOUR_ANSWER: FetchContent_MakeAvailable for Catch2
#

add_library(lib functions.hpp functions.cpp)
target_include_directories(lib PUBLIC ./)
target_compile_features(lib PUBLIC cxx_std_17)

add_executable(count main.cpp)
target_link_libraries(count lib)

#
# YOUR_ANSWER: tests executable
#

#
# YOUR_ANSWER: link tests with main function from Catch2
#
