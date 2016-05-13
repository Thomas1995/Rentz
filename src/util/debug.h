#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define D 1
#else
#define D 0
#endif

#define debug(...) if(D)\
                    fprintf(stderr, __VA_ARGS__)

#endif // DEBUG_H
