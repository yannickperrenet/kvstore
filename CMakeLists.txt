cmake_minimum_required(VERSION 3.22)
project(
    KVStore
    VERSION 1.0
    DESCRIPTION "Educational Key-Value store"
    LANGUAGES C CXX)

include(FetchContent)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    kvstore_unittest
    kvstore_unittest.cc kvstore.c kvstore.h
)

target_link_libraries(
    kvstore_unittest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(kvstore_unittest)
