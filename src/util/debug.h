#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

#define DEBUG 1
#define debug(...) if(DEBUG) fprintf(stderr, __VA_ARGS__); else 

#endif // DEBUG_H
