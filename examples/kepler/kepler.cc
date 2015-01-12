/*
 * This file is for testing energy conservation of a test particle
 * under the Keplerican potential for different integrators.
 */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <memory>
#include "constants.h"
#include "particle.h"
#include "force.h"
#include "integrator.h"
#include "euler.h"
#include "euler_semi_implicit.h"
#include "leapfrog.h"
#include "runge-kutta.h"

double G = 1;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <integrator> <output kind>\n", argv[0]);
    exit(1);
  }

  Particles p({
    Particle(100, 0),
    Particle(0, 0)  // test particle
    });
  p[1].x = 1.0;
  p[1].vy = 9.;

  double dt = 0.01;
  double tmax = 100.;
  double t;

  Force force;
  // setup the integrator
  Integrator *integrator = NULL;
  if ( strcmp(argv[1], "euler") == 0 ) {
    integrator = new Euler(dt, force);
  } else if ( strcmp(argv[1], "eulersi") == 0 ) {
    integrator = new Euler_SI(dt, force);
  } else if ( strcmp(argv[1], "leapfrog") == 0 ) {
    integrator = new Leapfrog(dt, force);
  } else if ( strcmp(argv[1], "rk4") == 0 ) {
    integrator = new RungeKutta4(dt, force);
  } else {
    printf("invalid integrator\n");
    exit(1);
  }

  if ( strcmp(argv[2], "orbit") == 0 ) {
    print_particles(p, std::cout);
    for (t = 0; t < tmax; t+=dt) {
      integrator->step(t, p);
      print_particles(p, std::cout);
    }
  } else if ( strcmp(argv[2], "energy") == 0 ) {
    double E = 0.;
    E = 0.5*pow(p[1].v(), 2) + potential(p, 1);
    printf("%20.15f\n", E);
    for (t = 0; t < tmax; t+=dt) {
      integrator->step(t, p);
      E = 0.5*pow(p[1].v(), 2) + potential(p, 1);
      printf("%20.15f\n", E);
    }
  } else {
    printf("invalid output kind\n");
    delete integrator;
    exit(1);
  }

  delete integrator;
  return 0;
}
