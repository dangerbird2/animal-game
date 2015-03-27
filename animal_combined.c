/**
 * this is a copy/pasted file containing all headers
 * and source files in the animal project
 * 
 * for a more reasonable build setup using the cmake
 * build system (http://www.cmake.org/) and git(http://git-scm.com/),
 * use the attached zip, or clone my project from github using
 * the command `git clone https://github.com/dangerbird2/animal-game.git`
 */

 /**
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief utility functions for libanimal
*/

#ifndef _SLS_UTIL_H_
#define _SLS_UTIL_H_

/**
@brief defines `__func__` if compiler doesn't support the macro 
*/
#ifndef __func__
#define __func__ "function unknown"
#endif

#include <stdio.h>

/**
 * @brief macro for determining max chars to
 * grab from input
 */
#define SLS_MAX_INPUT_SIZE 200

/**
 * @brief bool type enumeration
 */
typedef enum slsBool {
    SLS_FALSE = 0,
    SLS_TRUE = 1
} slsBool;


/**
 * @brief enum for user response codes
 * @detailed SLS_YES and SLS_NO are equivilent to
 * SLS_TRUE and SLS_FALSE respectively
 */
typedef enum slsResponse {
    SLS_NO = SLS_FALSE,
    SLS_YES = SLS_TRUE,
    SLS_UNDETERMINED,
    SLS_QUIT
} slsResponse;


/**
 * @brief copies a string to a heap-allocated buffer
 * @details you must free the returned pointer
 * 
 * @param str source string
 * @param n maximum string size
 * 
 * @return a malloced string copy of source str
 */
char *sls_stringalloc(char const *str, size_t n);

/**
 * @brief gets a line from an input stream
 * @details reads a line from a file, returning an allocated C-string
 * 
 * @param file pointer to file opened for reading
 * @param n maximum bytes to read
 * 
 * @return malloced string. Must be freed manually
 */
char *sls_getline(FILE *file, size_t n);


#endif /* _SLS_UTIL_H_ */

/**
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief definitions for binary tree data type
*/

#ifndef _ANIMAL_BTREE_H_
#define _ANIMAL_BTREE_H_

#include <stdlib.h>


typedef struct slsBNode slsBNode;
typedef struct slsBTree slsBTree;

/**
 * @brief function pointer type for copying btree data
 * @details a function pointer taking a const void pointer and
 * 
 * @param data pointer to data for copying
 * @return copy of input data
 */
typedef void *(*slsCopyFn)   (void const*data);

/**
 * @brief function pointer type for freeing btree data
 * @details takes a void pointer, to free associated memory
 * and close files
 * 
 * @param pointer to data [description]
 * @return [description]
 */
typedef void (*slsFreeFn)   (void *data);

/**
 * @brief enumeration used for determining
 * which child node to select. Usage TBD
 */
typedef enum slsChildSelector{
    SLS_CHILD_LEFT,
    SLS_CHILD_RIGHT
} slsChildSelector;


/**
 * @brief binary tree abstract data type
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

/**
 * @brief binary tree node for use in slsBTree type
 * @details stores a pointer to arbitrary data, whose
 * memory is 'owned' by the binary tree. If the tree is
 * constructed correctly, all memory will be freed when
 * tree is destoryed
 */
struct slsBNode {
    /**
     * @brief pointer to slsBTree which contains the node (
     * tree holds function pointers for determining
     * node's behavior)
     */
    slsBTree *tree;

    /**
     * @brief parent node
     */
    slsBNode *parent;

    /**
     * @brief left node
     */
    slsBNode *left;

    /**
     * @brief right node
     */
    slsBNode *right;

    /**
     * @brief data stored in node
     */
    void *val;
};

/**
 * @brief creates a new binary tree
 * @details [long description]
 * 
 * @param compare_fn callback for comparing values in two nodes
 * uses same function signature as qsort
 * @param copy_fn callback for copying values
 * @param free_fn callback for freeing node values
 * @return [description]
 */
slsBTree *sls_btree_new(
    slsCopyFn copy_fn,
    slsFreeFn free_fn);

/**
 * @brief destroys a binary tree and
 * all nodes it contains
 * @details [long description]
 * 
 * @param tree [description]
 */

void sls_btree_destroy(slsBTree *tree);

/**
 * @brief creates new binary tree node
 * @details [long description]
 * 
 * @param tree pointer to parent tree.
 * Must not be null
 * @param val pointer to value data
 * @param left (nullable) pointer to left node
 * @param right (nullable) pointer to right node
 * @return [description]
 */
slsBNode *sls_bnode_new(
    slsBTree *tree,
    void const *val,
    slsBNode *left,
    slsBNode *right
);

/**
 * @brief recursively destroys node and all child nodes
 * @details if node's btree contains a free function pointer,
 * it will call the function on each node's data field
 * 
 * @param node [description]
 */
void sls_bnode_destroy(slsBNode *node);



#endif /*_ANIMAL_BTREE_H_*/

/**
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief implementation of animal game
*/

#ifndef _ANIMAL_ANIMAL_H_
#define _ANIMAL_ANIMAL_H_

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
 * @brief the main game loop
 * @details begins the animal game.
 * read comments in the source for more explanation
 */
void sls_animal_run();

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

/*
main.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


int main(int argc, char **argv)
{
    sls_animal_run();
    
    return 0;
}

/*
util.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

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
    size_t len = 0;
    size_t i =0;
    size_t alloced_size = 16;
    line = calloc(sizeof(char), alloced_size);

    if (!line) {
        fprintf(stderr, "memory error! \n");
        return NULL;
    }

    for (i=0; i<n; ++i) {
        int c = fgetc(file);

        /* 
        if numer of characters exceeds allocated memory, 
        realloc array
        */
        if (i >= alloced_size) {
            alloced_size *= 2;
            line = realloc(line, alloced_size);
            if (!line) { /* make sure realloc worked correctly */
                line = NULL;
                break;
            }
        }
        /* end loop when you reach eof or newline */
        if (c == EOF || c == '\n') {
            break;
        } else {
            line[i] = c;

        }

    } 

    line[i] = '\0'; /* make sure string null-terminates */

    return line;
}


/*
btree.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

slsBTree *sls_btree_new(
    slsCopyFn copy_fn,
    slsFreeFn free_fn)
{
    slsBTree *tree = NULL;
    tree = calloc(sizeof(slsBTree), 1);
    /* ensure tree is allocated properly */
    if (tree) {
        tree->copy_fn = copy_fn;
        tree->free_fn = free_fn;

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
            sls_bnode_destroy(tree->head);
        }

        free(tree);
    } else {
        fprintf(stderr, "%s tree is NULL!\n", __func__);
    }
}

slsBNode *sls_bnode_new(
    slsBTree *tree,
    void const *val,
    slsBNode *left,
    slsBNode *right)
{
    slsBNode *node = NULL;
    if (!tree) {
        fprintf(
            stderr,
            "ERROR %s: tree must be nonnull!\n",
            __func__);
        return NULL;
    }
    node = calloc(sizeof(slsBNode), 1);
    if (node) {
        node->tree = tree;
        node->val = tree->copy_fn(val);
        node->left = left;
        node->right = right;
    } else {
        fprintf(
            stderr,
            "ERROR %s: malloc error!\n",
            __func__);
    }
    return node;
}

void sls_bnode_destroy(slsBNode *node)
{
    if (node) {
        /* try freeing node data */
        if (node->tree) {
            node->tree->free_fn(node->val);
        } else {
            fprintf(
                stderr,
             "WARNING %s: node->tree is null. Cannot free node data\n", __func__);
        }

        /**
         * recursively destroy child nodes
         */
        if (node->left) {
            sls_bnode_destroy(node->left);
        }
        if (node->right) {
            sls_bnode_destroy(node->right);
        }

        free(node);
    } else {
        fprintf(
            stderr,
            "WARNING %s: node is null\n", __func__);
    }
}

/*
animal.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/


slsBTree *sls_animaltree_new()
{
    slsBTree *tree = NULL;
    tree = sls_btree_new(
        sls_animal_copy,
        sls_animal_free);


    return tree;
}

void *sls_animal_copy(void const *data)
{
    slsAnimalData const *t_data = data;
    slsAnimalData *copied = NULL;
    size_t description_size = 1;

    if (t_data) {
        copied = sls_animal_new(
            t_data->is_species, 
            t_data->description);
    }


    return copied;
}
void sls_animal_free(void *data)
{
    slsAnimalData *t_data = data;
    if (t_data) {
        if (t_data->description) {
            free(t_data->description);
        }
        free(t_data);
    }
}

slsAnimalData *sls_animal_new(
    slsBool is_species, 
    char const *description)
{
    slsAnimalData *data = NULL;
    data = calloc(sizeof(slsAnimalData), 1);
    if (data) {
        data->is_species = is_species;

        size_t description_size = 1;
        if (description) {
            description_size = strlen(description);
        }
        data->description = sls_stringalloc(description, description_size);
        data->description[description_size] = '\0';
    }

    return data;
}

void sls_animal_run() 
{
    slsBTree *tree = NULL;
    slsBNode *current_node = NULL;
    /*
    Game setup.
    Randomly select a category and initialize the tree structure,
    with the category represented by the head node
    */
    /* a list of categories to start the tree */
    char const *categories[]={
        "fur",
        "no legs",
        "skeletons",
        "exoskeletons",
        "wings",
        "long noses",
        "four legs",
    };

    const size_t n_categories = sizeof(categories)/sizeof(char*);

    /*
    setup the game tree with a randomly selected category
    */
    tree = sls_animaltree_new();
    tree->head = sls_animalnode_new(
        tree, 
        SLS_FALSE,
        categories[rand() % n_categories]);
    current_node = tree->head;

    if (!tree || !current_node) {
        fprintf(stderr, "ERROR: memory failure. Game quiting");
        fprintf(stderr, "tree %lu, node %lu\n", (size_t)tree, (size_t)current_node);
        return;
    }

    /*
    GAME LOOP:
    while the is_running flag is true (not zero),
    the game will run.
    the loop will attempt to retrieve a valid response from the user.
    When a valid response is given, the function sls_decide_response
    will provide the business logic to traverse through the decision tree,
    or ask for additional info from user to 
    */
    slsBool is_running = SLS_TRUE;
    while(is_running) {
        slsResponse res = SLS_UNDETERMINED;
        if (!current_node) { 
        /* for memory safety, if current_node becomes NULL, set it to head of tree*/
            current_node = tree->head;
        }

        res = sls_ask_question(current_node);

        sls_print_node(stderr, current_node);

        if (res == SLS_QUIT) {
            fprintf(stderr, "Thanks for playing!\n"); 
            is_running = SLS_FALSE;

        } else if (res == SLS_UNDETERMINED) {
            fprintf(stderr, "Sorry, I could not read your answer\n");
        } else {
            if (!current_node) {
                current_node = tree->head;
            }
            
            current_node = sls_decide_response(
                current_node,
                res);
        }

    }

    sls_btree_destroy(tree);
}

slsResponse sls_parse_response(char const *res) 
{
    char const *ptr = res;
    const size_t len = strlen(res);
    slsResponse res_value;
    int i;

    /* search for first alphabetical value */
    for (i=0; i<len; ++i) {
        if (!isalpha(*ptr)) {
            ++ptr;
        } else { break; }
    }


    int c = tolower(*ptr);

    /* 
    use a switch statement to match the first letter in response
    to a valid response char (y, n, or q)
    */
    switch (c) {
        case 'y':
            res_value = SLS_YES;
            break;
        case 'n':
            res_value = SLS_NO;
            break;
        case 'q':
            res_value = SLS_QUIT;
            break;
        default:
            res_value = SLS_UNDETERMINED;
    }

    return res_value;
}

slsBNode *sls_animalnode_new(
    slsBTree *tree,
    slsBool is_species, 
    char const *description)
{
    slsAnimalData *data;
    slsBNode *node;
    data = sls_animal_new(is_species, description);
    node = sls_bnode_new(
        tree,
        data,
        NULL,
        NULL);

    sls_animal_free(data);
    return node;
}

slsResponse sls_ask_question(slsBNode *node)
{
    if (!node || !node->val) {
        return SLS_UNDETERMINED;
    }
    slsAnimalData *data = node->val;
    slsResponse res= SLS_UNDETERMINED;
    char const *prompt = data->is_species?
        "Are you thinking of a":
        "Does your animal have";
    
    while (res == SLS_UNDETERMINED) {
        char *line;
        fprintf(stderr, "\n%s %s?\n->", prompt, data->description);
        line = sls_getline(stdin, SLS_MAX_INPUT_SIZE);

        res = sls_parse_response(line);
        if (res == SLS_UNDETERMINED) {
            fprintf(stderr, "Sorry, I could not read your answer\n");
        }

        free(line);
    }
    
    return res;
}

slsBNode *sls_ask_new_category(slsBNode *node)
{
    if (!node || !node->val || !node->tree) {
        assert(SLS_FALSE);
        return NULL;
    }
    slsAnimalData *data = node->val;
    slsBNode *new_node = NULL;

    char *line = NULL;
    fprintf(stderr, 
        "\nWhat does your animal have that a %s doesn't:\n->",
        data->description);

    line = sls_getline(stdin, SLS_MAX_INPUT_SIZE);

    if (!line) {
        assert(SLS_FALSE);
        return NULL;
    }
    new_node = sls_animalnode_new(
        node->tree, 
        SLS_FALSE,
        line);

    free(line);

    return new_node;
}

slsBNode *sls_ask_new_animal(slsBNode *node)
{

    if (!node || !node->val || !node->tree) {
        assert(0);
        return NULL;
    }
    slsAnimalData *data = node->val;
    slsBNode *new_node = NULL;

    char *line;
    fprintf(stderr, 
        "\nI give up. what is your animal?:\n->");
    line = sls_getline(stdin, SLS_MAX_INPUT_SIZE);
    new_node = sls_animalnode_new(
        node->tree, 
        SLS_TRUE,
        line);
    free(line);

    return new_node;
}

void sls_print_node(FILE *stream, slsBNode const *node)
{
    if (!node || !node->val) {
        return;
    }
    char const *node_desc = ((slsAnimalData*)(node->val))->description;
    char const *parent_desc = node->parent?
        ((slsAnimalData*)(node->parent->val))->description:
        "no parent";

    char const *left = node->left?
        ((slsAnimalData*)(node->left->val))->description:
        "no left child";
    char const *right = node->right?
        ((slsAnimalData*)(node->left->val))->description:
        "no right child";

    fprintf(stream, "parent: %s\n", parent_desc);
    fprintf(stream, "  |\n");
    fprintf(stream, "  V\n");
    fprintf(stream, "node: %s\n", node_desc);
    fprintf(stream, "  | \\\n");
    fprintf(stream, "  V  V\n");
    fprintf(stream, "left: %s \nright %s\n", left, right);

}

slsBNode **sls_attempt_traversal(
    slsBNode *node, 
    slsResponse res)
{
    slsBNode **child_ptr = (res == SLS_YES)?
        &(node->right):
        &(node->left);

    return child_ptr;
}

slsBNode *sls_decide_response(
    slsBNode *node, 
    slsResponse res)
{
    /*
    TODO: simplify this logic
    it works right now, but it's pretty damn confusing
    */
    if (!node || !node->val || !node->tree) {
        assert(0);
        return NULL;
    }

    slsAnimalData *data = node->val;

    /* 
    first, see if we can traverse to a child node 
    */
    slsBNode *new_node = *sls_attempt_traversal(node, res);
    if (new_node) {
        char const *dirrection = (new_node == node->left)?
            "left": "right";

        fprintf(stderr, "moving to the %s node\n", dirrection);
        return new_node;
    }
    /*
    if the attempted traversal returns a null pointer,
    the program queries the user to expand its decision tree
    */

    if (res == SLS_YES && data->is_species) {
        /* in this event, the program guessed correctly, ending the game round */
        fprintf(stderr, "I guessed your animal!\nLet's play again\n");
        new_node = node->tree->head;
    } 
    else if (res == SLS_NO && data->is_species) {
        /* 
        here, the game guessed correctly, and the current question is an animal.
        It will ask the user for a new catagory to differentiate the user's (unkown)
        animal and the animal currently given
        */
        fprintf(stderr, "I guessed wrong.\n");
        new_node = sls_ask_new_category(node);
        slsBNode *parent = node->parent;
        node->parent = new_node;
        new_node->parent = parent;

        if (parent->left == node) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        new_node->left = node;

    } 
    else if (!data->is_species) {
        /*
        in this case, the current node describes a category.
        It will ask the user for the animal he/she was thinking about,
        
        */
        new_node = sls_ask_new_animal(node);
        new_node->parent = node;
        if (res == SLS_YES) {
            node->right = new_node;
        } else {
            node->left = new_node;
        }
    }

    /*
    return the head node, which restarts the game loop
    to the head of the decision tree
    */
    return node->tree->head;
}




