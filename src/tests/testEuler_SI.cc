#include "catch.hpp"

#include "../constants.h"
#include "particle.h"
#include "force.h"
#include "euler_semi_implicit.h"

double G = 1.;

TEST_CASE("Euler Semi Implicit", "[EulerSI]")
{
  //Create two particles
  Particles particles ({
    Particle (1e8, 1.),
    Particle (2e8, 1.)});

  REQUIRE(particles[0].mass == 1.e8);
  REQUIRE(particles[0].radius == 1.);
  REQUIRE(particles[1].mass == 2.e8);
  REQUIRE(particles[1].radius == 1.);

  particles[0].x = 0.;
  particles[0].y = 0.;      
  particles[0].z = 0.;
  
  particles[1].x = 0.;
  particles[1].y = 0.;      
  double z_0 = 1.e4;
  particles[1].z = z_0;

  particles[0].vx=1.;
  particles[0].vy=0.;
  particles[0].vz=0.;

  particles[1].vx=-1.;
  particles[1].vy=0.;
  particles[1].vz=0.;


  Force force;
  Integrator *integrator = NULL;
  integrator = new Euler_SI(1., force);

  REQUIRE_FALSE(integrator == NULL);

  int check;

  check = integrator->step(0, particles);

  REQUIRE(check == 0);

  REQUIRE(particles[0].vx == 1.0);
  REQUIRE(particles[0].vy == 0.0);
  REQUIRE(particles[0].vz == 2.0 );

  REQUIRE(particles[1].vx == -1.0);
  REQUIRE(particles[1].vy == 0.0);
  REQUIRE(particles[1].vz == -1.0 );

  REQUIRE(particles[0].x == 1.0);
  REQUIRE(particles[0].y == 0.0);
  REQUIRE(particles[0].z == 2.0 );

  REQUIRE(particles[1].x == -1.0);
  REQUIRE(particles[1].y == 0.0);
  REQUIRE(particles[1].z == -1.0  + z_0);

  delete integrator;

}
