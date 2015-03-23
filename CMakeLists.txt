cmake_minimum_required(VERSION 2.8)
project(animal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c90")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(ANIMAL_SRC
    src/animal.c
    src/btree.c
    src/util.c)


set(ANIMAL_TEST_SRC
    tests/test_run.cc
    tests/btree_test.cc
    tests/animal_test.cc)

add_subdirectory(extern/googletest)
include_directories(extern/googletest/include)

add_library(
    animal
    ${ANIMAL_SRC})

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