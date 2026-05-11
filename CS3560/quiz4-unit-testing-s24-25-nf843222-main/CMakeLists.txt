cmake_minimum_required(VERSION 3.16)
project(Othello)

enable_testing()

Include(FetchContent)
FetchContent_Declare(
    cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.1.1
)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2
)
FetchContent_MakeAvailable(cxxopts)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)
add_subdirectory(docs)

#
# Declaring libraries
#

add_library(game game.cpp game.hpp)
target_include_directories(game PUBLIC ./)

add_library(piece piece.cpp piece.hpp colors.hpp)
target_include_directories(piece PUBLIC ./)

add_library(othello othello.cpp othello.hpp colors.hpp)
target_link_libraries(othello game piece utils)
target_include_directories(othello PUBLIC ./)

add_library(utils utils.cpp utils.hpp)
target_include_directories(utils PUBLIC ./)

#
# Declare executable file.
#

add_executable(othello-game main.cpp)
target_link_libraries(othello-game PRIVATE othello cxxopts)
