/*
db.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <animal/animal_game.h>
#include <sqlite3.h>



/**
 * sql code for creating 
 */
static char const *SLS_CREATE_TABLES_SQL =
"CREATE TABLE IF NOT EXISTS trees ("
"   id INTEGER PRIMARY KEY,"
"   head_id INTEGER"
");"
"CREATE TABLE IF NOT EXISTS nodes ("
"   id INTEGER PRIMARY KEY,"
"   tree_id INTEGER,"
"   parent_id INTEGER,"
"   left_id INTEGER,"
"   right_id INTEGER,"
"   is_species INTEGER," /* boolean integer */
"   description TEXT"
");";


static char const *SLS_DROP_TABLES_SQL =
"DROP TABLE trees;"
"DROP TABLE nodes;";

char const *sls_get_create_table_sql()
{
    return SLS_CREATE_TABLES_SQL;
}
char const *sls_get_drop_table_statement()
{
    return SLS_DROP_TABLES_SQL;
}

slsBool sls_save_animal_tree(char const *path, slsBTree *tree)
{
    return SLS_FALSE;
}

slsBTree *sls_load_animal_tree(char const *path)
{
    return NULL;
}
