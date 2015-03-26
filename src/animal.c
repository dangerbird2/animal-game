/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include "animal.h"
#include "util.h"
#include <string.h>
#include <ctype.h>



slsAnimalTree_t *sls_animaltree_new()
{
    slsAnimalTree_t *tree = NULL;
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
    char *description)
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

slsAnimalNode_t *sls_animalnode_new(
    slsAnimalTree_t *tree,
    slsBool is_species, 
    char *description)
{
    slsAnimalData *data;
    slsAnimalNode_t *node;
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
    const size_t max_line = 100;
    if (!node || !node->val) {
        return NULL;
    }
    slsAnimalData *data = node->val;
    slsResponse res= SLS_UNDETERMINED;
    char const *prompt = data->is_species?
        "Are you thinking of a":
        "Does your animal";
    
    while (res == SLS_UNDETERMINED) {
        char *line;
        fprintf(stderr, "\n%s %s?\n->", prompt, data->description);
        line = sls_getline(stdin, max_line);

        res = sls_parse_response(line);
        if (res == SLS_UNDETERMINED) {
            fprintf(stderr, "Sorry, I could not read your answer\n");
        }

        free(line);
    }
    
    return res;

}


