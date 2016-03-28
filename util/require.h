#ifndef REQUIRE
#define REQUIRE

#include <iostream>
#include <string>
#include <cstdlib>

void require(bool condition, std::string err = "Generic Error") {
    if(!condition) {
        std::cerr << "Error: " << err;
        exit(0);
    }
}

#endif // REQUIRE
