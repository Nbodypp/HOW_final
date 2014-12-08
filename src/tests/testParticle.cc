#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdio.h>

#include "particle.h"

TEST_CASE("Create Particle", "[particle]") {
  Particle particle(5., 1.);
  REQUIRE(particle.mass == 5.);
  REQUIRE(particle.radius == 1.);
}

