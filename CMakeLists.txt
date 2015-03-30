cmake_minimum_required(VERSION 2.8)
project(animal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(ANIMAL_SRC
    src/animal.c
    src/btree.c
    src/db.c
    src/util.c)

set(ANIMAL_TEST_SRC
    tests/test_run.cc
    tests/btree_test.cc
    tests/animal_test.cc
    tests/game_test.cc
    tests/sql_test.cc)

## find sqlite3
find_library(SQLITE sqlite3)
if (${SQLITE} STREQUAL SQLITE-NOTFOUND)
    # if not found, set no sql compiler flag
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSLS_NO_SQL")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSLS_NO_SQL")
endif (${SQLITE} STREQUAL SQLITE-NOTFOUND)

add_subdirectory(extern/googletest)
include_directories(
    ${CMAKE_SOURCE_DIR}/extern/googletest/include 
    ${CMAKE_SOURCE_DIR}/include)

add_library(
    animal
    ${ANIMAL_SRC})

add_executable(
    animal_main
    src/main.c)
target_link_libraries(
    animal_main
    animal
    ${SQLITE})

add_executable(
    animal_tests
    ${ANIMAL_TEST_SRC})
target_link_libraries(
    animal_tests
    animal
    gtest
    gtest_main
    ${SQLITE})