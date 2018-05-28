// /*
//    Name: Jorge Guzman Nader
//    Date: 4/29/18
//    CS 362
//  */

// #ifndef TESTHELP_H_
// #define TESTHELP_H_

// #include <stddef.h>  
// #include <stdio.h>  

// /* wrapper for assert that permits side-effects within Verify362 statement
//  borrowed from: http://www.acm.uiuc.edu/sigops/roll_your_own/2.a.html*/

// void VerificationFailure(const char *exp, const char *file, const char *basefile, int line);

// #define Verify362(exp) if (exp) ; \
//   else VerificationFailure(#exp, __FILE__, __BASE_FILE__, __LINE__)

// /* error-handling wrappers; borrowed from textbook "computer systems: a
//  programmers perspective" by Randal Bryant and David O'Hallaron*/

// void unix_error(char *msg);

// void app_error(char *msg);

// /* wrappers for general utilities */

// void *Malloc(size_t size);

// void Free(void *ptr);

// /* wrapper for library functions */

// FILE *Fopen(const char * restrict filename, const char * restrict mode);

// void Fclose(FILE * restrict stream);

// #endif 