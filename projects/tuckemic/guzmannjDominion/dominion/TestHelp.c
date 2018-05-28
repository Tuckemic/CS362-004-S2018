// /*
//    Name: Jorge Guzman Nader
//    Date: 4/29/18
//    CS 362  
//  */

// #include <stddef.h>   
// #include <stdbool.h> 
// #include <stdio.h>   
// #include <stdlib.h>  
// #include <errno.h>   
// #include <string.h>  

// #include "TestHelp.h"

// /* wrapper for assert */

// void VerificationFailure(const char *exp, const char *file, const char *baseFile, int line) {
//   if (!strcmp(file, baseFile)) {
//     fprintf(stderr, "Verify362(%s) failed in file %s, line %d\n", exp, file, line);
//   } else {
//     fprintf(stderr, "Verify362(%s) failed in file %s (included from %s), line %d\n", exp, file, baseFile, line);
//   }
//   exit(EXIT_FAILURE);
// }

// /* unix style error */

// void unix_error(char *msg) {
//   fprintf(stderr, "%s: %s\n", msg, strerror(errno));
//   exit(EXIT_FAILURE);
// }

// /* application error */

// void app_error(char *msg) {
//   fprintf(stderr, "%s\n", msg);
//   exit(EXIT_FAILURE);
// }

// /* wrappers for general utilities */

// void *Malloc(size_t size) {
//   void *ptr = malloc(size);
//   if (ptr == NULL) {
//     unix_error("Malloc error");
//   }
//   return ptr;
// }

// void Free(void *ptr) {
//   free(ptr);
// }

// /* wrapper for library functions */

// FILE *Fopen(const char * restrict filename, const char * restrict mode) {
//   FILE *stream = fopen(filename, mode);
//   if (stream == NULL) {
//     unix_error("Fopen error");
//   }
//   return stream;
// }

// void Fclose(FILE * restrict stream) {
//   int result = fclose(stream);
//   if (result == EOF) {
//     unix_error("Fclose error");
//   }
// }