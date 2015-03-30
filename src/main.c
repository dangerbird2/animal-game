/*
main.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <animal/animal_game.h>


int main(int argc, char **argv)
{
    char const *db_path;
    if (argc > 1) {
        db_path = argv[1];
    } else {
        db_path = "animal.db";
    }
    fprintf(stderr, "loading database at file %s\n", db_path);

    sls_animal_run();
    return 0;
}