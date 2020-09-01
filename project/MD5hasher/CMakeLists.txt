cmake_minimum_required(VERSION 3.10)
project(MD5hasher)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_library(MD5hasherLib STATIC MD5hasher.hpp MD5hasher.cpp)
target_link_libraries(MD5hasherLib PRIVATE OpenSSL::SSL)

add_executable(MD5hasherTest MD5hasherTest.cpp)
target_link_libraries(MD5hasherTest MD5hasherLib GTest::GTest)
