cmake_minimum_required(VERSION 3.2)

project(lu C CXX)
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++20")

include_directories(include/)

aux_source_directory(src/ SRC)
add_executable(lu ${SRC})

target_include_directories(lu PUBLIC include/)
