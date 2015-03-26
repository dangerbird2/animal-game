/**
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief implementation of animal game
*/

#ifndef _ANIMAL_ANIMAL_H_
#define _ANIMAL_ANIMAL_H_

#include "util.h"
#include "btree.h"

/**
 * alias slsBTree
 */
typedef slsBTree slsAnimalTree_t;
typedef slsBNode slsAnimalNode_t;

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

/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
slsAnimalTree_t *sls_animaltree_new();

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param is_species [description]
 * @param description [description]
 * 
 * @return [description]
 */
slsAnimalData *sls_animal_new(
    slsBool is_species, 
    char *description);

slsAnimalNode_t *sls_animalnode_new(
    slsAnimalTree_t *tree,
    slsBool is_species, 
    char *description);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param data [description]
 * @return [description]
 */
void *sls_animal_copy(void const *data);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param data [description]
 */
void sls_animal_free(void *data);


/**
 * @brief parses a user response to a yes/no question
 * @details [long description]
 * 
 * @param res a string containing a user response
 * @return a response value cooresponding to user response
 */
slsResponse sls_parse_response(char const *res);

slsResponse sls_ask_question(slsBNode *node);


#endif /* _ANIMAL_ANIMAL_H_ */
