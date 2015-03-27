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
slsBTree *sls_animaltree_new();

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
    char const *description);

slsBNode *sls_animalnode_new(
    slsBTree *tree,
    slsBool is_species, 
    char const *description);

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

/**
 * @brief queries a response from the user
 * @details uses the description and question type
 * contained in a slsBNode
 * 
 * @param node [description]
 * @return [description]
 */
slsResponse sls_ask_question(slsBNode *node);

/**
 * @brief returns the node child appropriate
 * to the given response
 * @details [long description]
 * 
 * @param node [description]
 * @param res [description]
 * 
 * @return "left" node if res is SLS_YES, "right" node if SLS_NO
 */
slsBNode **sls_attempt_traversal(
    slsBNode *node, 
    slsResponse res);

slsBNode *sls_decide_response(slsBNode *node, slsResponse res);

slsBNode *sls_ask_new_category(slsBNode *node);

slsBNode *sls_ask_new_animal(slsBNode *node);

/**
 * @brief pretty printer for nodes containing animal data
 * @details currently prints descriptions of head, node, and children
 * 
 * TODO: implement ascii graphical printing function
 * 
 * @param stream file pointer for print output
 * @param node node containing slsAnimalData pointer in `node->val`
 */
void sls_print_node(FILE *stream, slsBNode const *node);



#endif /* _ANIMAL_ANIMAL_H_ */
