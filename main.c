/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "src/animal_game.h"



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

    slsAnimalTree_t *tree = sls_animaltree_new();
    tree->head = sls_animalnode_new(
        tree, 
        SLS_FALSE,
        categories[rand() % n_categories]);

    slsAnimalNode_t *current_node = tree->head;

    slsBool is_running = SLS_TRUE;
    while(is_running) {
        
        slsResponse res = sls_ask_question(current_node);

        if (res == SLS_QUIT) {
            fprintf(stderr, "Thanks for playing!\n"); 
            is_running = SLS_FALSE;

        } else if (res == SLS_UNDETERMINED) {
            fprintf(stderr, "Sorry, I could not read your answer\n");
        } else {

        }

    }

    sls_btree_destroy(tree);
}

int main(int argc, char **argv)
{
    run();
    
    return 0;
}