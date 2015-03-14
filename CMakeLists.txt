cmake_minimum_required(VERSION 3.1)
project(animal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")

set(ANIMAL_SRC
    src/animal.c)
add_library(
    animal
    ${ANIMAL_SRC} src/btree.h src/btree.c)

add_executable(
    animal_main
    main.c)
target_link_libraries(
    animal_main
    animal)