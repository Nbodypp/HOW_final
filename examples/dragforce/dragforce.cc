#include <iostream>
#include <random>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"
#include <math.h>

double G = 1;


void dragforce(Particles &particles) {
  double k = 0.1;
  for (auto &p : particles) {
    p.ax -= k * p.vx;
    p.ay -= k * p.vy;
    p.az -= k * p.vz;
  }
}

int main(int argc, char *argv[])
{

  Particles p ({
    Particle(1, 0),
    Particle(0, 0)  // test particle
    });
  p[1].x = 1.;
  p[1].vy = 1.;
  
  double dt = 0.01;
  double t = 0;
  double tmax = 10.;

  Force force;
  Leapfrog integrator (dt, force);
  force.add_force(dragforce);

  print_particles(p, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }
  return 0;
}
