/*
 * This is a boilerplate for setting up a custom N-body problem.
 */
#include <math.h>
#include <iostream>

#include "constants.h"
#include "particle.h"
#include "force.h"
#include "leapfrog.h"


double G = 1;

int main(int argc, char *argv[]) {
  // setup initial conditions
  Particle p1(1., 0.);
  p1.x = 0;
  Particle p2;
  p2.mass = 0.;  // zero-mass is test particle
  p2.x = 1.;
  p2.vy = 1.;

  double dt = 0.01;
  double t = 0;
  double tmax = 10.;

  // setup force model
  Force force;
  // to add additional forces
  // force.add_force(&forcefunc);

  // setup integrator
  Leapfrog integrator(dt, force);

  // print initial conditions
  print_particles(p, std::cout);
  // main loop
  for (t = 0; t < tmax; t+=dt) {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }
  return 0;
}
