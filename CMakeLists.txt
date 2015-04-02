cmake_minimum_required(VERSION 2.8)
project(animal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(SLS_GENERATE_DOCS TRUE
    CACHE BOOL "generate documentation with doxygen")

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

# find doxygen and generate docs
find_package(Doxygen)
if (DOXYGEN_FOUND AND SLS_GENERATE_DOCS)
    configure_file(
        ${CMAKE_SOURCE_DIR}/doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen")
endif(DOXYGEN_FOUND AND SLS_GENERATE_DOCS)

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