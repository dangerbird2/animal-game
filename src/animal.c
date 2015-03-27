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



