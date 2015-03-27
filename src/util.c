/*
util.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <animal/animal_game.h>



char *sls_stringalloc(char const* str, size_t n)
{
    char *new_str = NULL;
    new_str = calloc(sizeof(char), n + 1);
    if (new_str && str) {
        new_str[0] = '\0';
        int i =0;
        for (i=0; i<n; ++i) {
            new_str[i] = str[i];

            if (str[i] == '\0') {
                break;
            }
        }

    }

    return new_str;
}

char *sls_getline(FILE *file, size_t n)
{
    char *line = NULL;
    size_t i =0;
    size_t alloced_size = 16;
    line = calloc(sizeof(char), alloced_size);

    if (!line) {
        fprintf(stderr, "memory error! \n");
        return NULL;
    }

    for (i=0; i<n; ++i) {
        int c = fgetc(file);

        /* 
        if numer of characters exceeds allocated memory, 
        realloc array
        */
        if (i >= alloced_size) {
            alloced_size *= 2;
            line = realloc(line, alloced_size);
            if (!line) { /* make sure realloc worked correctly */
                line = NULL;
                break;
            }
        }
        /* end loop when you reach eof or newline */
        if (c == EOF || c == '\n') {
            break;
        } else {
            line[i] = c;

        }

    } 

    line[i] = '\0'; /* make sure string null-terminates */

    return line;
}


