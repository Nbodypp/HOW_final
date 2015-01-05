#include "catch.hpp"

#include "collision.h"
#include "particle.h"


TEST_CASE("Checking collision algorithm works", "[collision]")
{
  //Create two identical particles
  Particles particles (2, Particle (5.e5, 1.e3));

  REQUIRE(particles[0].mass == 5.e5);
  REQUIRE(particles[0].radius == 1.e3);
  REQUIRE(particles[1].mass == 5.e5);
  REQUIRE(particles[1].radius == 1.e3);

  SECTION("See if two particles placed on top of each "
          "other are marked as colliding") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.;
    particles[1].y = 0.;      
    particles[1].z = 0.;

    REQUIRE(collision_check_all(particles) == 1);
  }

  SECTION("See if two particles somewhat off center "
          "from  each other are marked as colliding") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.;
    particles[1].y = 0.;      
    particles[1].z = 999.;

    REQUIRE(collision_check_all(particles) == 1);
  }

  SECTION("See if two particles significantly off center "
          "from  each other are marked as colliding") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.;
    particles[1].y = 0.;      
    particles[1].z = 1999.;

    REQUIRE(collision_check_all(particles) == 1);
  }

  SECTION("See if two particles close to each other but not touching "
          "are marked as NOT colliding") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.;
    particles[1].y = 0.;      
    particles[1].z = 2001.;

    REQUIRE(collision_check_all(particles) == 0);
  }

  SECTION("See if two particles far away from each other "
          "are marked as NOT colliding") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.;
    particles[1].y = 0.;      
    particles[1].z = 1.e6;

    REQUIRE(collision_check_all(particles) == 0);
  }

  SECTION("See if the function has correct capabilities for handling "
          "multiple particles") {
    particles[0].x = 0.;
    particles[0].y = 0.;      
    particles[0].z = 0.;

    particles[1].x = 0.995e5;
    particles[1].y = 0.995e5;      
    particles[1].z = 0.995e5;

    particles.push_back(Particle(5.e3,1.e2));
    particles.push_back(Particle(2.e5,1.e4));

    REQUIRE(particles[2].mass == 5.e3);
    REQUIRE(particles[2].radius == 1.e2);
    REQUIRE(particles[3].mass == 2.e5);
    REQUIRE(particles[3].radius == 1.e4);

    particles[2].x = 1.e5;
    particles[2].y = 1.e5;      
    particles[2].z = 1.e5;

    particles[3].x = 1.e5;
    particles[3].y = 1.e4;      
    particles[3].z = 1.e10;

    REQUIRE(collision_check_all(particles) == 1);
  }   
}