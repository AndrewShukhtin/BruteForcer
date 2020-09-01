cmake_minimum_required(VERSION 3.10)
project(brutef)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O2 -Wall")

find_package(GTest REQUIRED)
include_directories(${GTEST_INLCUDE_DIR})

add_subdirectory(project/BruteForcer)
add_subdirectory(project/MD5hasher)

add_executable(brutef project/main.cpp)
target_link_libraries(brutef BruteForcerLib)
target_include_directories(brutef PRIVATE project/BruteForcer)