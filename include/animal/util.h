/**
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2

@file
@brief utility functions for libanimal
*/

#ifndef _SLS_UTIL_H_
#define _SLS_UTIL_H_

/**
@brief defines `__func__` if compiler doesn't support the macro
*/
#ifndef __func__
#define __func__ "function unknown"
#endif

#include <stdio.h>

/**
 * @brief macro for determining max chars to
 * grab from input
 */
#define SLS_MAX_INPUT_SIZE 200

/**
 * @brief bool type enumeration
 */
typedef enum slsBool { SLS_FALSE = 0, SLS_TRUE = 1 } slsBool;

/**
 * @brief enum for user response codes
 * @detailed SLS_YES and SLS_NO are equivilent to
 * SLS_TRUE and SLS_FALSE respectively
 */
typedef enum slsResponse {
  SLS_NO = SLS_FALSE,
  SLS_YES = SLS_TRUE,
  SLS_UNDETERMINED,
  SLS_QUIT
} slsResponse;

/**
 * @brief copies a string to a heap-allocated buffer
 * @details you must free the returned pointer
 *
 * @param str source string
 * @param n maximum string size
 *
 * @return a malloced string copy of source str
 */
char *sls_stringalloc(char const *str, size_t n);

/**
 * @brief gets a line from an input stream
 * @details reads a line from a file, returning an allocated C-string
 *
 * @param file pointer to file opened for reading
 * @param n maximum bytes to read
 *
 * @return malloced string. Must be freed manually
 */
char *sls_getline(FILE *file, size_t n);

/**
 * @brief implementation of strncmp which disregards case
 * @details [long description]
 *
 * @param a first string
 * @param b second string
 *
 * @return (from http://www.cplusplus.com/reference/cstring/strncmp/)
 *  <0   the first character that does not match has a lower value in str1 than
 *in str2
 *   0   the contents of both strings are equal
 *   >0  the first character that does not match has a greater value in str1
 *than in str2
 */
int sls_strncmp_nocase(char const *a, char const *b, size_t size);

#endif /* _SLS_UTIL_H_ */
