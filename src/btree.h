/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#ifndef _ANIMAL_BTREE_H_
#define _ANIMAL_BTREE_H_

#include <stdlib.h>

typedef struct slsBNode slsBNode;
typedef struct slsBTree slsBTree;

typedef int (*slsCompareFn) (void const*,  void const*);
typedef void (*slsFreeFn)   (void*);


struct slsBTree {
    size_t key_size;
    size_t val_size;

    slsCompareFn compare_fn;

    slsFreeFn key_free_fn;
    slsFreeFn val_key_fn;

    slsBNode *head;
};

struct slsBNode {
    slsBTree *tree;
    slsBNode *left;
    slsBNode *right;

    void *key;
    void *val;
};

slsBTree *sls_btree_new(
    size_t key_size, 
    size_t val_size,
    slsCompareFn compare_fn,
    slsFreeFn key_free_fn,
    slsFreeFn val_free_fn);

void sls_btree_destroy(slsBTree *tree);


#endif //_ANIMAL_BTREE_H_
