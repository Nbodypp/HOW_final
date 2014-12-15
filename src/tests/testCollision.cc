#define CATCH_CONFIG_MAIN
#include "../vendor/catch.hpp"
#include <stdio.h>

#include "../collision.h"
#include "../particle.h"


TEST_CASE("Checking collision algorithm works", "[collision]")
{

  Particles particles;
  Collision col;

  //Create two identical particles
  particles.push_back(std::unique_ptr<Particle>(new Particle(5.e5,1.e3)));
  particles.push_back(std::unique_ptr<Particle>(new Particle(5.e5,1.e3)));

  REQUIRE(particles[0]->mass == 5.e5);
  REQUIRE(particles[0]->radius == 1.e3);
  REQUIRE(particles[1]->mass == 5.e5);
  REQUIRE(particles[1]->radius == 1.e3);


  SECTION("See if two particles placed on top of each "
          "other are marked as colliding")
    {

      particles[0]->x = 0.;
      particles[0]->y = 0.;      
      particles[0]->z = 0.;

      particles[1]->x = 0.;
      particles[1]->y = 0.;      
      particles[1]->z = 0.;

      REQUIRE(col.collision_check_all(particles) == 1);

    }

  SECTION("See if two particles somewhat off center "
          "from  each other are marked as colliding")
    {

      particles[0]->x = 0.;
      particles[0]->y = 0.;      
      particles[0]->z = 0.;

      particles[1]->x = 0.;
      particles[1]->y = 0.;      
      particles[1]->z = 999.;


      REQUIRE(col.collision_check_all(particles) == 1);

    }


  SECTION("See if two particles significantly off center "
          "from  each other are marked as colliding")
    {


      particles[0]->x = 0.;
      particles[0]->y = 0.;      
      particles[0]->z = 0.;

      particles[1]->x = 0.;
      particles[1]->y = 0.;      
      particles[1]->z = 1999.;


      REQUIRE(col.collision_check_all(particles) == 1);

    }

  SECTION("See if two particles close to each other but not touching "
          "are marked as NOT colliding")
    {

      particles[0]->x = 0.;
      particles[0]->y = 0.;      
      particles[0]->z = 0.;

      particles[1]->x = 0.;
      particles[1]->y = 0.;      
      particles[1]->z = 2001.;

      REQUIRE(col.collision_check_all(particles) == 0);

    }

  SECTION("See if two particles far away from each other "
          "are marked as NOT colliding")
    {

      particles[0]->x = 0.;
      particles[0]->y = 0.;      
      particles[0]->z = 0.;

      particles[1]->x = 0.;
      particles[1]->y = 0.;      
      particles[1]->z = 1.e6;


      REQUIRE(col.collision_check_all(particles) == 0);

    }

}
