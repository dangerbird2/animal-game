/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#ifndef _ANIMAL_BTREE_H_
#define _ANIMAL_BTREE_H_

#include <stdlib.h>
#include "util.h"

typedef struct slsBNode slsBNode;
typedef struct slsBTree slsBTree;

typedef int (*slsCompareFn) (void const*,  void const*);
typedef void *(*slsCopyFn)   (void const*);
typedef void (*slsFreeFn)   (void*);

typedef enum slsChildSelector{
    SLS_CHILD_LEFT,
    SLS_CHILD_RIGHT
} slsChildSelector;


/**
 * @brief binary tree ADT
 * @details provides a wrapper type for
 * a tree made up of allocated nodes.
 * The structure also provides a crude
 * virtual table for the nodes, providing
 * callbacks necessary for their logic
 */
struct slsBTree {
    
    /**
     * callback for copying values
     * in nodes
     */
    slsCopyFn copy_fn;
    /**
     * callback for freeing values in nodes
     */
    slsFreeFn free_fn;

    slsBNode *head;
};

struct slsBNode {
    slsBTree *tree;

    slsBNode *left;
    slsBNode *right;

    void *val;
};

/**
 * @brief: creates a new binary tree
 * @details: [long description]
 * 
 * @param compare_fn: callback for comparing values in two nodes
 * uses same function signature as qsort
 * @param copy_fn: callback for copying values
 * @param free_fn: callback for freeing node values
 * @return [description]
 */
slsBTree *sls_btree_new(
    slsCopyFn copy_fn,
    slsFreeFn free_fn);

/**
 * @brief destroys a binary tree and
 * |TODO| all nodes it contains
 * @details [long description]
 * 
 * @param tree [description]
 */

void sls_btree_destroy(slsBTree *tree);

/**
 * @brief creates new binary tree node
 * @details [long description]
 * 
 * @param tree: pointer to parent tree.
 * Must not be null
 * @param val: pointer to value data
 * @param left: (nullable) pointer to left node
 * @param right (nullable) pointer to right node
 * @return [description]
 */
slsBNode *sls_bnode_new(
    slsBTree *tree,
    void const *val,
    slsBNode *left,
    slsBNode *right
);

void sls_bnode_destroy(slsBNode *node);



#endif //_ANIMAL_BTREE_H_
