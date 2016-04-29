#ifndef REQUIRE_H
#define REQUIRE_H

#include <iostream>
#include <string>
#include <cstdlib>

void require(bool condition, std::string err = "Generic Error");

#define DEBUG

#ifdef DEBUG
#define D 1
#else
#define D 0
#endif

#define debug(...) if(D)\
                    fprintf(stderr, __VA_ARGS__)

#endif // REQUIRE_H
