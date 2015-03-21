/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include "animal.h"
#include "util.h"
#include <string.h>

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
