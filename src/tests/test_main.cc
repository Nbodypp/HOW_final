#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// The purpose of this two line file is to speed up CATCH test compilation
// as recommended at
// https://github.com/philsquared/Catch/blob/master/docs/slow-compiles.md
// Do not include `#define CATCH_CONFIG_MAIN` in individual test files.

#include "constants.h"

double G = 1.;  // Use G = 1 for all tests