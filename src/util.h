/*
Created by Steven Shea on 3/14/15.
for CMPS 1600, project 2
*/

#ifndef _SLS_UTIL_H_
#define _SLS_UTIL_H_

/**
 * boolean enum type
 */
typedef enum slsBool {
    SLS_FALSE = 0,
    SLS_TRUE = 1
} slsBool;


/**
 * @brief: copies a string to a heap-allocated buffer
 * @details [long description]
 * 
 * @param str: source string
 * @param n: maximum string size
 * 
 * @return: a malloced string copy of source str
 */
char *sls_stringalloc(char const *str, size_t n);

#endif /* _SLS_UTIL_H_ */
