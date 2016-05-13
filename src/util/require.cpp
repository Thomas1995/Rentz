#include "require.h"

void require(bool condition, std::string err) {
    if(!condition) {
        std::cerr << "Error: " << err;
        exit(0);
    }
}
