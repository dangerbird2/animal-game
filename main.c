/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include "src/animal.h"
#include "src/btree.h"
#include "src/util.h"


int main(int argc, char **argv)
{
    char *line = sls_getline(stdin, 1000);
    if (line) {
        printf("%s\n", line);
        free(line);

    } 
    return 0;
    
}