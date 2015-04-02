/**
db.h
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief functions for sqlite storage of node data
*/
#ifndef ANIMAL_DB_H
#define ANIMAL_DB_H


#include "btree.h"

/**
 * @brief saves a tree to a sqlite3 database
 * @details at the given path
 *
 * @param path path to a sqlite3 database
 * use ":memory:" for an in-memory database
 * @param tree pointer to a animal-data storing
 * slsBTree
 *
 * @return [description]
 */
slsBool sls_save_animal_tree(char const *path, slsBTree *tree);

/**
 * @brief loads and parses a sqlite3 database
 * @details for use in animal guessing game
 *
 * @param path path to a sqlite3 database
 * @return if the given path stores valid game data,
 * a slsBTree pointer containing data described
 */
slsBTree *sls_load_animal_tree(char const *path);


#ifndef SLS_NO_SQL
#include <sqlite3.h>

typedef struct slsAnimalNodeSchema slsAnimalNodeSchema;
/**
 * @brief struct used for mapping sql data
 * to a slsBNode structure
 * @details [long description]
 *
 */
struct slsAnimalNodeSchema {
    long id;
    long tree_id;
    long parent_id;
    long left_id;
    long right_id;

    slsAnimalData data;
};

/**
 * @brief callback function type for sqlite3 queries
 * @details used as a parameter for sqlite3_exec
 * more details on https://www.sqlite.org/c3ref/exec.html
 *
 * @param n_cols number of columns query result
 * @param col_data_array [description]
 * @param col_name_array [description]
 * @return sqlite3 return code
 */
typedef int (*slsSqlCallbackFn) (
    void *data,
    int n_cols,
    char **col_data_array,
    char **col_name_array);

/**
 * @brief logging macro to check for errors
 * @details accepts a char pointer. If the pointer
 * is non-null, it prints it to stderr and returns
 * the current function with given rval
 *
 * @param \_err\_ if non-null, an malloced error message
 * @param \_rval\_ value to return if failure occurs
 */
#define SLS_ERRCHECK(_err_, _rval_) do {            \
        if((_err_) != NULL) {                       \
            fprintf(stderr, "ERROR: %s\n", (_err_));\
            free((_err_));                          \
            return (_rval_);                        \
        }                                           \
    } while(0)

/**
 * @brief same as SLS_ERRCHECK, but causes function to exit
 * void on error
 */
#define SLS_ERRCHECK_VOID(_err_) do {               \
        if((_err_) != NULL) {                       \
            fprintf(stderr, "ERROR: %s\n", (_err_));\
            free((_err_));                          \
            return;                                 \
        }                                           \
    } while(0)


/**
 * @brief gets CREATE TABLE statement
 * @details for storing btree and bnode data
 * @return a static constant string
 */
char const *sls_get_create_table_sql();

/**
 * @brief gets DELETE TABLE statement
 * @details for clearing game database
 * @return a static constant string
 */
char const *sls_get_drop_table_statement();


#endif /* DSLS_NO_SQL */
#endif /* ANIMAL_DB_H */

