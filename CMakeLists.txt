cmake_minimum_required(VERSION 3.1)
project(animal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y")

set(ANIMAL_SRC
    src/animal.c)


set(ANIMAL_TEST_SRC
    tests/test_run.cc
    tests/btree_test.cc)

add_subdirectory(extern/googletest)
include_directories(extern/googletest/include)

add_library(
    animal
    ${ANIMAL_SRC} src/btree.h src/btree.c)

add_executable(
    animal_main
    main.c)
target_link_libraries(
    animal_main
    animal)

add_executable(
    animal_tests
    ${ANIMAL_TEST_SRC})
target_link_libraries(
    animal_tests
    animal
    gtest
    gtest_main)