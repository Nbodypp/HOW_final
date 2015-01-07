#include "catch.hpp"
#include <iostream>

#include "constants.h"
#include "particle.h"


TEST_CASE("Test Particle class", "[particle]") {
  Particle p1;
  p1.mass = 5.;
  p1.radius = 1.;
  p1.x  = 3.;  p1.y  = 4.;
  p1.vx = 6.;  p1.vz = 8.;

  Particle p2(1., 1.);

  SECTION("check if particle attributes are correct") {
    REQUIRE(p1.mass == 5.);
    REQUIRE(p1.radius == 1.);
    REQUIRE(p1.x == 3.);
    REQUIRE(p1.y == 4.);
    REQUIRE(p1.z == 0.);
    REQUIRE(p1.vx == 6.);
    REQUIRE(p1.vy == 0.);
    REQUIRE(p1.vz == 8.);

    REQUIRE(p2.mass == 1.);
    REQUIRE(p2.radius == 1.);
    REQUIRE(p2.x == 0.);
    REQUIRE(p2.y == 0.);
    REQUIRE(p2.z == 0.);
    REQUIRE(p2.vx == 0.);
    REQUIRE(p2.vy == 0.);
    REQUIRE(p2.vz == 0.);
  }

  SECTION("check the distance between two particles") {
    double d12 = p1.d(p2);
    double d21 = p2.d(p1);
    REQUIRE(d12 == 5.);
    REQUIRE(d12 == d21);
  }

  SECTION("check the velocities of the particles") {
    REQUIRE(p1.v() == 10.);
    REQUIRE(p2.v() == 0.);
  }

  SECTION("check the kinetic energy of the particles") {
    REQUIRE(p1.Ekin() == 250.);
    REQUIRE(p2.Ekin() == 0.);
  }

  SECTION("Test Particles typedef") {
    Particles p({p1, p2});
    SECTION("calculate potential") {
      REQUIRE(potential(p, 0) == -G*p2.mass/p2.d(p1));
      REQUIRE(potential(p, 1) == -G*p1.mass/p1.d(p2));
    }
  }
}

TEST_CASE("Test misc functions on particles state", "[particle]") {
  Particles p({
    Particle(5., 1.),
    Particle(2., 4.),
    Particle(3., 3.)});
  // put some random numbers in
  p[0].x = 3.3;
  p[0].vx = 22;
  p[1].y = -30;
  p[2].vz = 6.23e8;

  SECTION ("save to a binary file") {
    std::ofstream f ("test.bin", std::ios::binary);
    if (f.is_open()) {
      save_particles(p, f);
      f.close();
    } else {
      std::cerr << "error opening a file\n";
    }
  }

  SECTION ("write to stdout") {
    print_particles(p, std::cout);
  }

  SECTION ("write to an ascii flle") {
    std::ofstream f ("test.dat");
    if (f.is_open()) {
      print_particles(p, f);
      f.close();
    }
    else {
      std::cerr << "error opening a file\n";
    }
  }
}

