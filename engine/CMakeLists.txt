cmake_minimum_required(VERSION 3.20)

project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main 
    src/main.cpp 
    src/display.cpp 
    src/bitboard.cpp 
    src/input.cpp 
    src/board.cpp 
    src/movegen.cpp)

target_include_directories(main PRIVATE include)
target_compile_options(main PRIVATE -Wall -Wextra -Wshadow -Wconversion)