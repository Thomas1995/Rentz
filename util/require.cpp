#ifndef REQUIRE_IMPL
#define REQUIRE_IMPL

#include "require.h"

void require(bool condition, std::string err) {
    if(!condition) {
        std::cerr << "Error: " << err;
        exit(0);
    }
}

#endif // REQUIRE_IMPL
