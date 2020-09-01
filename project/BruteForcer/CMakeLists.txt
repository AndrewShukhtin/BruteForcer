cmake_minimum_required(VERSION 3.10)
project(BruteForcer)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_library(BruteForcerLib STATIC BruteForcer.hpp BruteForcerConfig.hpp BruteForcer.cpp)

find_package(Threads REQUIRED)

target_link_libraries(BruteForcerLib PUBLIC MD5hasherLib Threads::Threads)
target_include_directories(BruteForcerLib PRIVATE ../MD5hasher)

add_executable(BruteForcerTest BruteForcerTest.cpp)
set_target_properties(BruteForcerTest PROPERTIES LINK_FLAGS --coverage)
set_target_properties(BruteForcerTest PROPERTIES COMPILE_FLAGS --coverage)
target_link_libraries(BruteForcerTest BruteForcerLib GTest::GTest)