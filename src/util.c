/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

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

    return line;
}
