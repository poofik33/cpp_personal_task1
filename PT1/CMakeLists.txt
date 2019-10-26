cmake_minimum_required(VERSION 3.12)
project(PersTask1 C)
project(test_gtest CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


set(LIB_SOURCE_FILES
        post.c
        tests.c input.c input.h)

add_library(work_with_posts STATIC ${LIB_SOURCE_FILES})

add_executable(PersTask1 main.c)

target_link_libraries(PersTask1 work_with_posts)

find_package( GTest REQUIRED )

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_gtest tests_gtest.cpp)

enable_testing()
add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(tests_gtest -fprofile-arcs)

target_link_libraries(tests_gtest ${GTEST_LIBRARIES} pthread)
target_link_libraries(tests_gtest work_with_posts)
