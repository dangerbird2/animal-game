/*
db.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <animal/animal_game.h>
#include <assert.h>

#ifndef SLS_NO_SQL /* if cmake can find sqlite */

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
    "   left_id INTEGER,"
    "   right_id INTEGER,"
    "   is_species INTEGER," /* boolean integer */
    "   description TEXT"
    ");";

/*
insert statement format for a node
*/
static char const *SLS_INSERT_NODE_SQL =
    "INSERT INTO nodes ("
    " left_id,"
    " right_id,"
    " is_species,"
    " description)"
    "VALUES (%li, %li, %i, '%s');";

/*
update statement for a node which already has an id
*/
static char const *SLS_UPDATE_NODE_SQL =
    "UPDATE nodes"
    "SET parent_id=%li,"
    " left_id=%li,"
    " right_id=%li,"
    " is_species=%i,"
    " description=%s,"
    "WHERE id = %li;";

static char const *SLS_DROP_TABLES_SQL =
    "DROP TABLE IF EXISTS trees;"
    "DROP TABLE IF EXISTS nodes;";

char const *sls_get_create_table_sql() { return SLS_CREATE_TABLES_SQL; }
char const *sls_get_drop_table_statement() { return SLS_DROP_TABLES_SQL; }

slsBool sls_save_animal_tree(char const *path, slsBTree *tree) {
  if (!tree || !tree->head || !path) {
    assert(SLS_FALSE);
    return SLS_FALSE;
  }
  sqlite3 *db = NULL;
  int rc = sqlite3_open(path, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "ERROR: %s\n", sqlite3_errstr(rc));
    return SLS_FALSE;
  }

  /*
  reset table in database (as opposed to updating it)
  */
  char *err;
  rc = sqlite3_exec(db, SLS_DROP_TABLES_SQL, NULL, NULL, &err);
  SLS_ERRCHECK(err, SLS_FALSE);

  rc = sqlite3_exec(db, SLS_CREATE_TABLES_SQL, NULL, NULL, &err);
  SLS_ERRCHECK(err, SLS_FALSE);

  rc = sls_save_animalnode(db, tree->head);
  if (rc < 0) {
    fprintf(stderr, "WARNING: could not save tree\n");
  }

  rc = sqlite3_close(db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "ERROR: %s\n", sqlite3_errstr(rc));
    return SLS_FALSE;
  }

  return SLS_TRUE;
}

slsBTree *sls_load_animal_tree(char const *path) { 
  slsBTree tree = NULL;
  tree sls_animaltree_new();
}

long sls_save_animalnode(sqlite3 *db, slsBNode *node) {
  char *query = NULL;
  long id = -1;
  int rc;

  if (/*!db || */ !node || !node->val) {
    fprintf(stderr, "WARNING: invalid parameters\n");
    return -1l;
  }

  slsAnimalData *data = node->val;

  if (node->left) {
    data->left_id = sls_save_animalnode(db, node->left);
  } else {
    data->left_id = -1l;
  }

  if (node->right) {
    data->right_id = sls_save_animalnode(db, node->right);
  } else {
    data->right_id = -1l;
  }

  /*
  build a sql query using sqlite's mprintf function.
  it creates a printf-style string buffer, allocated on heap to the
  required length
  */
  query = sqlite3_mprintf(SLS_INSERT_NODE_SQL, data->left_id, data->right_id,
                          (int)data->is_species, data->description);

  if (query) {
    char *err;
    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    sqlite3_free(query);

    SLS_ERRCHECK(err, -1);

    id = sqlite3_last_insert_rowid(db);
    

    data->db_id = id;

  }

  return id;
}

#else
/*
SLS_NO_SQL is defined
use dummy functions to let user know files can't be saved
 */

slsBool sls_save_animal_tree(char const *path, slsBTree *tree) {
  fprintf(stderr,
          "program is compiled without sqlite3\n"
          "save and loading are disabled");
  return SLS_FALSE;
}

slsBTree *sls_load_animal_tree(char const *path) {
  fprintf(stderr,
          "program is compiled without sqlite3\n"
          "save and loading are disabled");
  return NULL;
}

#endif /* SLS_NO_SQL */
