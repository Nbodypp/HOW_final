#include "catch.hpp"

#include "constants.h"
#include "particle.h"
#include "force.h"
#include "leapfrog.h"

double G = 1.;

TEST_CASE("Leapfrog_with_particles", "[Leapfrog]")
{
  //Create two particles
  Particles particles ({
    Particle (1., 1.),
    Particle (2., 1.)});

  REQUIRE(particles[0].mass == 1.);
  REQUIRE(particles[0].radius == 1.);
  REQUIRE(particles[1].mass == 2.);
  REQUIRE(particles[1].radius == 1.);

  particles[0].x = 0.;
  particles[0].y = 0.;      
  particles[0].z = 2.;
  
  particles[1].x = 0.;
  particles[1].y = 0.;      
  particles[1].z = 0.;

  particles[0].vx=0.;
  particles[0].vy=0.;
  particles[0].vz=-1.;

  particles[1].vx=0.;
  particles[1].vy=0.;
  particles[1].vz=1.;


  Force force;
  Integrator *integrator = NULL;
  integrator = new Leapfrog(1., force);

  REQUIRE_FALSE(integrator == NULL);

  int check;

  check = integrator->step(0, particles);

  REQUIRE(check == 0);

  REQUIRE(particles[0].vx == 0.0);
  REQUIRE(particles[0].vy == 0.0);
  REQUIRE(particles[0].vz == 5.8611111111111111111);

  REQUIRE(particles[1].vx == 0.0);
  REQUIRE(particles[1].vy == 0.0);
  REQUIRE(particles[1].vz == -2.43055555555555555);

  REQUIRE(particles[0].x == 0.0);
  REQUIRE(particles[0].y == 0.0);
  REQUIRE(particles[0].z == 0.75);

  REQUIRE(particles[1].x == 0.0);
  REQUIRE(particles[1].y == 0.0);
  REQUIRE(particles[1].z == 1.125);

  delete integrator;

}


