/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#ifndef _ANIMAL_ANIMAL_H_
#define _ANIMAL_ANIMAL_H_

#include "util.h"
#include "btree.h"

/**
 * alias slsBTree
 */
typedef slsBTree slsAnimalTree_t;

typedef struct slsAnimalData slsAnimalData;
struct slsAnimalData {
    /* 
    indicates whether node describes a species or a category
    */
    slsBool is_species;
    /*
    animal description: either animal name or
    animal category
    */
    char *description;
};

slsAnimalTree_t *sls_animaltree_new();

slsAnimalData *sls_animal_new(
    slsBool is_species, 
    char *description);

void *sls_animal_copy(void const *data);


void sls_animal_free(void *data);

/**
 * @brief: copies a string to a heap-allocated buffer
 * @details [long description]
 * 
 * @param str: source string
 * @param n: maximum string size
 * 
 * @return: a malloced string copy of source str
 */
char *sls_stringalloc(char const *str, size_t n);



#endif //_ANIMAL_ANIMAL_H_
