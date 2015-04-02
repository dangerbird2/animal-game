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
    /**
    indicates whether node describes a species or a category
    */
    slsBool is_species;
    /*
    animal description: either animal name or
    animal category
    */
    char *description;
    /*
     * sqlite id keys
     */

    /**
     * @brief id in database *nodes* table
     */
    long db_id;
    /**
     * @brief id of right node in database *nodes* table
     */
    long left_id;

    /**
     * @brief id of left node in database *nodes* table
     */
    long right_id;
};

/******************
* ANIMAL DATA FUNCTIONS
*******************/

/**
 * @brief create animal data structure
 * @details destroy with sls_animal_free
 *
 * @param is_species [description]
 * @param description [description]
 *
 * @return [description]
 */
slsAnimalData *sls_animal_new(
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
 * @brief free animal data
 * @details [long description]
 *
 * @param data [description]
 */
void sls_animal_free(void *data);

/******************
* ANIMAL BINARY NODE MANIPULATION
*******************/

/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
slsBTree *sls_animaltree_new();

/**
 * @brief create a new animal slsBNode
 * @details [long description]
 *
 * @param tree [description]
 * @param is_species [description]
 * @param description [description]
 * @return [description]
 */
slsBNode *sls_animalnode_new(
    slsBTree *tree,
    slsBool is_species,
    char const *description);

/**
 * @brief retrieve is_species from animalnode
 *
 * @param node slsBNode containing slsAnimalData pointer
 * @return SLS_TRUE if node contains a species
 */
slsBool sls_animalnode_get_isspecies(
    slsBNode const  *node);


void sls_animalnode_store_child_descriptions(
    slsBNode const *node,
    char const** left_desc,
    char const** right_desc);

/**
 * @brief retrieve description from animalnode
 *
 * @param node slsBNode containing slsAnimalData pointer
 * @return animal data description
 */
char const *sls_animalnode_get_description(
    slsBNode const  *node);

/**
 * @brief pretty printer for nodes containing animal data
 * @details currently prints descriptions of head, node, and children
 *
 * TODO: implement ascii graphical printing function
 *
 * @param stream file pointer for print output
 * @param node node containing slsAnimalData pointer in `node->val`
 */
void sls_animalnode_print_node(FILE *stream, slsBNode const *node);



/******************
* ANIMAL GAME LOGIC
*******************/

/**
 * 
 */

/**
 * @brief the main game loop
 * @details begins the animal game.
 * read comments in the source for more explanation
 * 
 * @param argc pointer to program argv
 * @param argv program argc
 */
void sls_animal_run(int const *argc, char **argv);

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
 * @param stream input stream
 * @param node [description]
 * @return [description]
 */
slsResponse sls_ask_question(FILE *stream, slsBNode *node);

/**
 * @brief returns the node child appropriate
 * to the given response
 * @details [long description]
 *
 * @param node pointer to current animalData node
 * @param res user's response
 *
 * @return "left" node if res is SLS_YES, "right" node if SLS_NO
 */
slsBNode **sls_attempt_traversal(
    slsBNode *node,
    slsResponse res);


/**
 * @brief traverse to next node
 * @details asks user for needed information
 *
 * @param stream input stream
 * @param node animal node
 * @param res user node
 * @return node pointer indicating the next
 * node to traverse
 */
slsBNode *sls_decide_response(
    FILE *stream,
    slsBNode *node,
    slsResponse res);


/**
 * @brief asks user for new category,
 * @details and
 * inserts category node in front of given node
 *
 * @param stream input stream
 * @param node animal node
 *
 * @return [description]
 */
slsBNode *sls_ask_new_category(FILE *stream, slsBNode *node);

/**
 * @brief asks user for new category,
 * @details and
 * inserts category node in front of given node
 *
 * @param stream input stream
 * @param node category node
 *
 * @return [description]
 */
slsBNode *sls_ask_new_animal(FILE *stream, slsBNode *node);



#endif /* _ANIMAL_ANIMAL_H_ */
