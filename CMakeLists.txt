cmake_minimum_required(VERSION 3.2)

project(lu C CXX)
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++20")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(src/)
add_executable(lu_test test/main.cpp)
target_link_libraries(lu_test gtest_main)

include(GoogleTest)
gtest_discover_tests(lu_test)

find_package(Boost 1.76.0 COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(include/)

aux_source_directory(src/ SRC)
add_executable(lu ${SRC})

target_include_directories(lu PUBLIC include/)
target_include_directories(lu PUBLIC ${Boost_LIBRARIES})

