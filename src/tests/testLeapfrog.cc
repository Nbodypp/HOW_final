//Test the euler integration scheme

#include "catch.hpp"

#include "constants.h"
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "simpleintegration.h"


TEST_CASE("Leapfrog Single Particle", "[integrator]")
{
  //Create a particle
  Particles particles ({
    Particle (1., 1.)});

  REQUIRE(particles[0].mass == 1.);
  REQUIRE(particles[0].radius == 1.);

  //Initial conditions of the particle
  double x0 = 1.;
  double vy0 = 1.;
  particles[0].x = x0;
  particles[0].y = 0.;
  particles[0].z = 0.;

  particles[0].vx = 0.;
  particles[0].vy = vy0;
  particles[0].vz = 0.;

  int check;

  //Set up Force object and set up additional force
  //defined in simpleintegration.cc
  Force force(0);
  check = force.add_force(SimpleIntegration);
  REQUIRE(check == 0);

  //Set up the Integrator object
  Integrator *integrator = NULL;
  double dt = 1.0;
  integrator = new Leapfrog(dt, force);

  REQUIRE_FALSE(integrator == NULL);

  //Have integrator take first step, make sure it returns
  check = integrator->step(0, particles);

  REQUIRE(check == 0);

  //Check the values from this first step
  REQUIRE(particles[0].x == x0 + dt*(.5*dt*ax_0));
  REQUIRE(particles[0].y == dt*(vy0 + .5*dt*ay_0));
  REQUIRE(particles[0].z == dt*(.5*dt*az_0));
  
  REQUIRE(particles[0].vx == ax_0*dt);
  REQUIRE(particles[0].vy == vy0 + 2.*dt);
  REQUIRE(particles[0].vz == 3.*dt);

  //Check velocity over several steps
  //Position is not checked here because large time
  //step doesn't allow Leapfrog method to converge on analytic answer
  //very well
  for (int i=2; i<52; ++i){
    check = integrator->step(i*dt, particles);
    REQUIRE(check == 0);
    
    REQUIRE(particles[0].vx == ax_0*(i*dt));
    REQUIRE(particles[0].vy == vy0 + ay_0*(i*dt));
    REQUIRE(particles[0].vz == az_0*(i*dt));
  }

  delete integrator;

  //Reset initial velocity and position of particle to test
  //serious integration
  dt = 1.e-8;
  integrator = new Leapfrog(dt, force);
  REQUIRE_FALSE(integrator == NULL);

  particles[0].x = x0;
  particles[0].y = 0.;      
  particles[0].z = 0.;

  particles[0].vx=0.;
  particles[0].vy=vy0;
  particles[0].vz=0.;

  int maxint = 100000000;

  //Run the integrator over many timesteps
  for (int i=0; i<maxint; ++i){
    integrator->step(i*dt, particles);
  }
  //Now, check that the final values of the integration make sense
  
  //Analytic solution of x(t) with constant acceleration:
  // x_f = x_0 + v_x_0 * t + .5 * a_x * t * t
  CHECK( (particles[0].x - (x0 + .5*ax_0*(dt*maxint)*(dt*maxint))) <= 1e-8);
  CHECK( (particles[0].y - (vy0*(dt*maxint) + .5*ay_0*(dt*maxint)*(dt*maxint))) < 1e-8);
  CHECK( (particles[0].z - (.5 * az_0*(dt*maxint)*(dt*maxint))) < 1e-8);
  
  //Analytic solution of v(t) with constant acceleration:
  // v_f = v_0 + a * t
  CHECK( (particles[0].vx - ax_0*(dt*maxint)) <= 1e-8);
  CHECK( (particles[0].vy - (vy0 + ay_0*(dt*maxint))) <= 1e-8);
  CHECK( (particles[0].vz - az_0*(dt*maxint)) <= 1e-8);
  
  delete integrator;
}



TEST_CASE("Leapfrog Many Particle", "[integrator]"){
  Particles particles;

  const double basemass = 1.;
  const double baseradius = 1.;
  const double basey = 1.;
  const double basevx = 1.;

  //Set up a bunch of particles
  int numparticles = 10;
  for (int i=0; i<numparticles; ++i){
    particles.push_back(Particle(i*basemass,i*baseradius));
    particles.back().y = i*basey;
    particles.back().vx = i*basevx;
  }

  int check;
  
  //Set up Force object and set up additional force
  //defined in simpleintegration.cc
  Force force(0);
  check = force.add_force(SimpleIntegration);
  REQUIRE(check == 0);
  
  //Set up the Integrator object
  Integrator *integrator = NULL;
  double dt = 1.e-8;
  integrator = new Leapfrog(dt, force);
  
  REQUIRE_FALSE(integrator == NULL);


  //Check over several steps
  int numint = 100000;
  for (int i=0; i<numint; ++i){
    check = integrator->step(i*dt, particles);
    REQUIRE(check == 0);
  }
  
  
  for (int j=0; j<numparticles; ++j){
    //Analytic solution of x(t) with constant acceleration:
    // x_f = x_0 + v_x_0 * t + .5 * a_x * t * t
    CHECK( (particles[j].x - (j*basevx*numint*dt + .5*ax_0*(dt*numint)*(dt*numint))) <= 1e-8);
    CHECK( (particles[j].y - (j*basey + .5*ay_0*(dt*numint)*(dt*numint))) < 1e-8);
    CHECK( (particles[j].z - (.5 * az_0*(dt*numint)*(dt*numint))) < 1e-8);
    
    //Analytic solution of v(t) with constant acceleration:
    // v_f = v_0 + a * t
    CHECK( (particles[j].vx - (j*basevx + ax_0*(dt*numint))) <= 1e-8);
    CHECK( (particles[j].vy - ay_0*(dt*numint)) <= 1e-8);
    CHECK( (particles[j].vz - az_0*(dt*numint)) <= 1e-8);
  }
 
  delete integrator;
}
