cmake_minimum_required(VERSION 3.24)
project(BigNumber)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

#add_executable(BigNumber
#        src/big_number.cpp
#        src/big_number.h)


# ---------------------
# Google Test
# ---------------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(TEST_FILES
        src/big_number.cpp
        tst/big_number_test.cpp)

add_executable(tst ${TEST_FILES})

target_link_libraries(tst gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tst)
