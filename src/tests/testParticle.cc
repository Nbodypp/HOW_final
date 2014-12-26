#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

#include "particle.h"

TEST_CASE("Create Particles", "[particle]") {
  Particle particle(5., 1.);
  REQUIRE(particle.mass == 5.);
  REQUIRE(particle.radius == 1.);

}

TEST_CASE("Save state to a binary file", "[particle]") {
  Particles p ({
    Particle(5., 1.),
    Particle(2., 4.),
    Particle(3., 3.)});
  // put some random numbers in
  p[0].x = 3.3;
  p[0].vx = 22;
  p[1].y = -30;
  p[2].vz = 6.23e8;
  std::ofstream f ("test.bin", std::ios::binary);
  if (f.is_open())
  {
    save_particles(p, f);
    f.close();
  }
  else {
    std::cerr << "error opening a file\n";
  }
}

