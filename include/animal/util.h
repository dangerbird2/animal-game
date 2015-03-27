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
typedef enum slsBool {
    SLS_FALSE = 0,
    SLS_TRUE = 1
} slsBool;


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


#endif /* _SLS_UTIL_H_ */
