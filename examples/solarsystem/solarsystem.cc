#include <iostream>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"

double G = 1;

int main(int argc, char *argv[])
{
  Particles p ({
    Particle (1., 0.),        // sun
    Particle (3.01473e-6, 0)  // earth
    });

  p[1].x = 0.2913994;
  p[1].vy = 1.8568;

  double dt = 0.001;
  double t = 0;
  double tmax = 100.;

  Force force;
  Leapfrog integrator (dt, force);
  print_particles(p, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }
  return 0;
}
