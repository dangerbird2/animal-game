/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#ifndef _ANIMAL_ANIMAL_H_
#define _ANIMAL_ANIMAL_H_

#include "util.h"

/**
 * alias slsBTree
 */
typedef slsBTree slsAnimalTree_t;

typedef struct slsAnimalData slsAnimalData;
struct slsAnimalData {
    /* 
    indicates whether node describes a species or a category
    */
    slsBool isSpecies;
    /*
    animal description: either animal name or
    animal category
    */
    char *description;
};

slsAnimalTree_t *sls_animaltree_new();

void *sls_animal_copy(void const *data);
void sls_animal_free(void *data);



#endif //_ANIMAL_ANIMAL_H_
