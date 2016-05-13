#ifndef REQUIRE_H
#define REQUIRE_H

#include <iostream>
#include <string>
#include <cstdlib>

void require(bool condition, std::string err = "Generic Error");

#endif // REQUIRE_H
