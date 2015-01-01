#include <iostream>
#include <random>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"
#include <math.h>

double G = 1;

void gravity(Particles &particles) {
  double r;
  double M = 1.;
  for (auto &p : particles) {
    r = sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    p.ax += G*M*(-p.x) / pow(r,3);
    p.ay += G*M*(-p.y) / pow(r,3);
    p.az += G*M*(-p.z) / pow(r,3);
  }
}

int main(int argc, char *argv[])
{
  Particles p (2, Particle(0, 0));  // two test particles
  p[0].x = 1.;
  p[0].vy = 1.;
  p[1].x = 2.;
  p[1].vy = 0.5;
  
  double dt = 0.01;
  double t = 0;
  double tmax = 10.;

  Force force;
  Leapfrog integrator (dt, force);
  force.add_force(gravity);

  print_particles(p, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }
  return 0;
}
