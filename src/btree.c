/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include "btree.h"
#include <stdlib.h>
#include <stdio.h>


slsBTree *sls_btree_new(
    size_t key_size, 
    size_t val_size,
    slsCompareFn compare_fn,
    slsFreeFn key_free_fn,
    slsFreeFn val_free_fn)
{
    slsBTree *tree = NULL;
    tree = calloc(sizeof(slsBTree), 1);
    /* ensure tree is allocated properly */
    if (tree) {
        /* assign tree data from prototype struct */
        slsBTree proto = {
            key_size, /* .key_size */
            val_size, /* .val_size */
            compare_fn, /* .compare_fn */
            key_free_fn, /* .key_free_fn */
            val_free_fn /* .val_free_fn */
        };
        *tree = proto;
        tree->head = NULL;
    } else {
        fprintf(stderr, "%s tree is NULL!\n", __func__);
    }
    return tree;
}

void sls_btree_destroy(slsBTree *tree)
{
    if (tree) {
        
        if (tree->head) {
            /*
            TODO: node destruction data
            */
        }

        free(tree);
    } else {
        fprintf(stderr, "%s tree is NULL!\n", __func__);
    }
}