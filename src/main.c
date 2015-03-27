/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <animal/animal_game.h>



void run() 
{
    srand(time(NULL) * clock());
    char const *animals[]={
        "sheep",
        "cow",
        "lizard",
        "dog",
        "moose"
    };
    const size_t n_animals = sizeof(animals)/sizeof(char*);

    char const *categories[]={
        "fur",
        "slime",
        "wings",
        "long noses",
        "four legs",
        "domestic breeds"
    };

    const size_t n_categories = sizeof(animals)/sizeof(char*);

    const size_t line_max = 200;

    slsBTree *tree = sls_animaltree_new();
    tree->head = sls_animalnode_new(
        tree, 
        SLS_FALSE,
        categories[rand() % n_categories]);

    slsBNode *current_node = tree->head;

    slsBool is_running = SLS_TRUE;
    while(is_running) {
        
        slsResponse res = sls_ask_question(current_node);
        slsAnimalData *data = current_node->val;

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
            #if 0
            slsBNode **next_node =
                (res == SLS_YES)?
                    &current_node->right:
                    &current_node->left;
            if (*next_node) {
                current_node = *next_node;
            } else {
                slsBNode *new_next;
                if (data->is_species) {
                    new_next = sls_ask_new_category(current_node);

                    new_next->parent = current_node->parent;
                    current_node->parent = new_next;
                    new_next->right = current_node;

                } else {
                    
                    new_next = sls_ask_new_animal(current_node);

                    new_next->parent = current_node;
                    *next_node = new_next;
                }
                fprintf(stderr, "Thank you, let's start again\n");
                current_node = tree->head;

            }
            #endif

        }

    }

    sls_btree_destroy(tree);
}

int main(int argc, char **argv)
{
    run();
    
    return 0;
}