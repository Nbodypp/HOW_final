//STILL UNDER CONSTRUCTION

#include "catch.hpp"

#include "constants.h"
#include "particle.h"
#include "force.h"
#include "runge-kutta.h"


TEST_CASE("Runge-Kutta 4th Order", "[RK4]")
{
  // Create two particles
  Particles particles ({
    Particle (1., 1.),
    Particle (1., 1.)});

  REQUIRE(particles[0].mass == 1.);
  REQUIRE(particles[0].radius == 1.);
  REQUIRE(particles[1].mass == 1.);
  REQUIRE(particles[1].radius == 1.);

  particles[0].x = 0.;
  particles[0].y = 0.;      
  particles[0].z = 0.;
  
  particles[1].x = 0.;
  particles[1].y = 0.;      
  double z_0 = 10.;
  particles[1].z = z_0;

  particles[0].vx=1.;
  particles[0].vy=0.;
  particles[0].vz=0.;

  particles[1].vx=-1.;
  particles[1].vy=0.;
  particles[1].vz=0.;

  Force force;
  Integrator *integrator = NULL;
  integrator = new RungeKutta4(1., force);

  REQUIRE_FALSE(integrator == NULL);

  int check;
  check = integrator->step(0, particles);

  REQUIRE(check == 0);
  
  

//  REQUIRE(particles[0].vx == 1.0);
//  REQUIRE(particles[0].vy == 0.0);
//  REQUIRE(particles[0].vz == 0.0 );

// REQUIRE(particles[1].vx == -1.0);
//  REQUIRE(particles[1].vy == 0.0);
//  REQUIRE(particles[1].vz == 0.0 );

//  REQUIRE(particles[0].x == 0.0);
//  REQUIRE(particles[0].y == 0.0);
//  REQUIRE(particles[0].z == 0.0 );

//  REQUIRE(particles[1].x == 0.0);
//  REQUIRE(particles[1].y == 0.0);
//  REQUIRE(particles[1].z == 0.0  + z_0);

  delete integrator;
}
