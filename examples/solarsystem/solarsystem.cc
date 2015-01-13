#include <iostream>
#include "particle.h"
#include "force.h"
#include "runge-kutta.sixthorder.h"
#include "constants.h"

double G = 1;

int main(int argc, char *argv[])
{
  Particles p ({
    Particle (1., 0.),        // Sun
    Particle (1.65956463e-7, 0.), // Mercury
    Particle (2.44699613e-6, 0.), // Venus
    Particle (3.01473e-6, 0.),  // Earth
    Particle (3.22604696e-7, 0.) // Mars
    });

  p[1].x = 0.1127656;
  p[1].vy = 2.9110307;

  p[2].x = 0.2106707;
  p[2].vy = 2.15254;
  
  p[3].x = 0.2913994;
  p[3].vy = 1.8568;

  p[4].x = 0.444069336;
  p[4].vy = 1.479487;


  double dt = 0.001;
  double t = 0;
  double tmax = 100.;

  Force force;
  RungeKutta6 integrator (dt, force);
  print_particles(p, std::cout);
  int counter = 0;
  for (t = 0; t < tmax; t+=dt) {
    integrator.step(t, p);
    if(counter % 12 == 0) {
      print_particles(p, std::cout);
    }
    counter++;
  }
  return 0;
}
