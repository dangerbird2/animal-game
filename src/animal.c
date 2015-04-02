/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <animal/animal_game.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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
    if (!t_data || !t_data->description) {
        fprintf(stderr, 
            "ERROR %s %i:\n\tdata or description fields are NULL\n", 
            __FILE__,
            __LINE__);
        return NULL;
    }

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
        data->db_id = -1;
        data->left_id = -1;
        data->right_id = -1;
    }

    return data;
}

slsBNode *sls_animalnode_new(
    slsBTree *tree,
    slsBool is_species, 
    char const *description)
{
    slsAnimalData *data;
    slsBNode *node;
    data = sls_animal_new(is_species, description);
    assert(data);
    node = sls_bnode_new(
        tree,
        data,
        NULL,
        NULL);

    sls_animal_free(data);
    return node;
}

void sls_animal_run(int const *argc, char **argv)
{
    slsBTree *tree = NULL;
    slsBNode *current_node = NULL;
    FILE *stream = stdin;
    char const *db_path;

    /*
    retrieve database path from program arguments
    */
    if (*argc > 1) {
        db_path = argv[1];
    } else {
        db_path = "animal.db";
    }
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

    /* try loading tree from database */
    tree = sls_load_animal_tree(db_path);
    if (!tree) {
        /*
        if no database is loaded,
        setup the game tree with a randomly selected category
        */
        tree = sls_animaltree_new();
        tree->head = sls_animalnode_new(
        tree, 
        SLS_FALSE,
        categories[rand() % n_categories]);
        current_node = tree->head;
    }


    

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

        res = sls_ask_question(stream, current_node);

        sls_animalnode_print_node(stderr, current_node);

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
                stream,
                current_node,
                res);
        }

    }

    sls_btree_destroy(tree);
}

slsResponse sls_parse_response(char const *res) 
{
    char const *ptr = res;
    const size_t len = SLS_MAX_INPUT_SIZE;
    slsResponse res_value;

    size_t i;

    /* search for first alphabetical value */
    for (i=0; i<len; ++i) {
        if (!isalpha(*ptr)) {
            ++ptr;
        } else { break; }
    }


    int c = tolower(*ptr);

    if ((sls_strncmp_nocase("quit", res, len) == 0) ||
        (sls_strncmp_nocase("q", res, len) == 0)) {

        res_value = SLS_QUIT;

    } else if ((sls_strncmp_nocase("yes", res, len) == 0) ||
        (sls_strncmp_nocase("y", res, len) == 0)) {

        res_value = SLS_YES;
    } else if ((sls_strncmp_nocase("no", res, len) == 0) ||
        (sls_strncmp_nocase("n", res, len) == 0)) {

        res_value = SLS_NO;

    } else {
        res_value = SLS_UNDETERMINED;
    }

    return res_value;
}

slsResponse sls_ask_question(
    FILE *stream, 
    slsBNode *node)
{
    assert(stream);
    if (!node || !node->val || !stream) {
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

slsBNode *sls_ask_new_category(
    FILE *stream, 
    slsBNode *node)
{
    assert(stream);
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

    line = sls_getline(stream, SLS_MAX_INPUT_SIZE);

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

slsBNode *sls_ask_new_animal(
    FILE *stream, 
    slsBNode *node)
{
    assert(stream);

    if (!node || !node->val || !node->tree) {
        assert(SLS_FALSE);
        fprintf(stderr, "ERROR %s: node or one of its fields are NULL\n", __func__);
        return NULL;
    }
    slsBNode *new_node = NULL;

    char *line;
    fprintf(stderr, 
        "\nI give up. what is your animal?:\n->");
    line = sls_getline(stream, SLS_MAX_INPUT_SIZE);
    new_node = sls_animalnode_new(
        node->tree, 
        SLS_TRUE,
        line);
    free(line);

    return new_node;
}

slsBool sls_animalnode_get_isspecies(
    slsBNode const  *node)
{
    if (!node || !node->val) {
        assert(SLS_FALSE);
        return SLS_FALSE;
    }
    return ((slsAnimalData*)(node->val))->is_species;
}

char const *sls_animalnode_get_description(
    slsBNode const *node)
{
    char const *desc;
    if (!node) {
        desc = NULL;
    } else {
        desc = ((slsAnimalData*)(node->val))->description;
    }
    return desc;
}

void sls_animalnode_store_child_descriptions(
    slsBNode const *node,
    char const** left_desc,
    char const** right_desc)
{
    if (!node) {
        *left_desc = NULL;
        *right_desc = NULL;
        return;
    }
    *left_desc = (node->left)?
        sls_animalnode_get_description(node->left):
        NULL;
    *right_desc = (node->right)?
        sls_animalnode_get_description(node->right):
        NULL;
}

void sls_animalnode_print_node(FILE *stream, slsBNode const *node)
{
    if (!node) {
        assert(SLS_FALSE);
        return;
    }
    /*
    declare char pointers for descriptions.
    */
    char const *left_left;
    char const *left;
    char const *left_right;
    char const *node_desc;
    char const *right_left;
    char const *right;
    char const *right_right;

    /* set strings to node descriptiosn
    (if node doesn't exist, pointer will be set to NULL)*/
    node_desc = sls_animalnode_get_description(node);
    sls_animalnode_store_child_descriptions(node, &left, &right);
    sls_animalnode_store_child_descriptions(node->left, &left_left, &left_right);
    sls_animalnode_store_child_descriptions(node->right, &right_left, &right_right);

    /* make sure all strings are non-null */
    left_left =     left_left?      left_left: "no node";
    left =          left?           left: "no node";
    left_right =    left_right? left_right: "no node";
    node_desc =     node_desc?      node_desc: "no node";
    right_left =    right_left?     right_left: "no node";
    right =         right?          right: "no node";
    right_right =   right_right?    right_right: "no node";

    /* print da string */
    fprintf(stderr, "    n--%s\n", left_left);
    fprintf(stderr, "    |\n");
    fprintf(stderr, "n--%s\n", left);
    fprintf(stderr, "|   |\n");
    fprintf(stderr, "|   y--%s\n", left_right);
    fprintf(stderr, "|\n");
    fprintf(stderr, "|\n");
    fprintf(stderr, "%s\n", node_desc);
    fprintf(stderr, "|\n");
    fprintf(stderr, "|\n");
    fprintf(stderr, "|   n--%s\n", right_left);
    fprintf(stderr, "|   |\n");
    fprintf(stderr, "y--%s\n", right);
    fprintf(stderr, "    |\n");
    fprintf(stderr, "    y--%s\n", right_right);
}

slsBNode **sls_attempt_traversal(
    slsBNode *node, 
    slsResponse res)
{
    if (!node) {
        assert(SLS_FALSE);
        return NULL;
    }
    slsBNode **child_ptr = (res == SLS_YES)?
        &(node->right):
        &(node->left);

    return child_ptr;
}

slsBNode *sls_decide_response(
    FILE *stream,
    slsBNode *node, 
    slsResponse res)
{
    /*
    TODO: simplify this logic
    it works right now, but it's pretty damn confusing
    */
    assert(stream);
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
        new_node = sls_ask_new_category(stream, node);
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
        new_node = sls_ask_new_animal(stream, node);
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



