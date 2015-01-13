#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "force.h"
#include "integrator.h"
#include "euler.h"
#include "leapfrog.h"
#include "runge-kutta.h"
#include "constants.h"

double G = 6.67384e-8;

/** Updates particle acceleration based on a central force field*/
void external_potential(Particles& particles) {
  // sun located at the origin
  const double mass = 1.99e33;  // g

  double r;
  for (auto &p : particles) {
    r = sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    p.ax += -G*mass*p.x / pow(r, 3);
    p.ay += -G*mass*p.y / pow(r, 3);
    p.az += -G*mass*p.z / pow(r, 3);
  }
}

int main(int argc, char *argv[]) {

  Particle earth(5.97219e27, 0.);
  earth.x = 1.49597871e13;
  earth.vy = 2.979e6;

  Particle moon(7.34767309e25, 0.);
  moon.x = 1.49980371e13;
  moon.vy = 3.081e6;

  Particles p = {earth, moon};

  double t = 0;
  double dt = 200.;
  double tmax = 1.6e7;

  // Setup the force model
  Force force;
  force.add_force(&external_potential);

  // Setup the integrator
  Leapfrog integrator(dt, force);
  print_particles(p, std::cout);

  for (t = 0; t < tmax; t+=dt) {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }

  return 0;
}
