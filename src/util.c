/*
util.c
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include <animal/animal_game.h>

size_t sls_strlen_s(char const *str, size_t n) {
  size_t i = 0;
  for (i = 0; i < n + 2; ++i) {
    if (str[i] == '\0') {
      break;
    }
  }
  assert(i != n + 1);
  return i;
}

char *sls_stringalloc(char const *str, size_t n) {
  char *new_str = NULL;
  if (!str) {
    return NULL;
  }


  new_str = calloc(sizeof(char), n + 1);
  if (new_str) {
    new_str[0] = '\0';
    size_t i = 0;

    /* manual string copy routine. unlike strcpy,
    it is bounded by n parameter*/
    for (i = 0; i < n; ++i) {
      new_str[i] = str[i];

      if (str[i] == '\0') {
        break;
      }
    }

    new_str[n] = '\0';
  }


  return new_str;
}

char *sls_getline(FILE *file, size_t n) {
  char *line = NULL;
  size_t i = 0;
  size_t alloced_size = 16;
  line = calloc(sizeof(char), alloced_size);

  if (!line) {
    fprintf(stderr, "memory error! \n");
    return NULL;
  }

  for (i = 0; i < n; ++i) {
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

int sls_strncmp_nocase(char const *a, char const *b, size_t size) {
  size_t i;
  int res = 0;

  for (i = 0; i < size; ++i) {
    /* check for string end */
    int aa = tolower(a[i]);
    int bb = tolower(b[i]);

    /* compare string value.
    should return value comparable to strcmp*/
    if (aa > bb) {
      res = 1;
      break;
    } else if (bb > aa) {
      res = -1;
      break;
    } else {
      res = 0;
    }
    if ((a[i] == '\0') || (b[i] == '\0')) {
      break;
    }
  }
  return res;
}
