/*
 * This file is for demonstrating a resonant interaction
 * in a binary-single system.
 */
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
#include <math.h>
#include <cstring>

double G = 1;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <integrator> <output kind>\n", argv[0]);
    exit(1);
  }

  Particles p({
    Particle(1., 0),
    Particle(1., 0),
    Particle(1., 0)
    });
  p[0].x  = -1.;
  p[0].y  = 0.;
  p[0].z  = 0.;
  p[0].vx = 0.;
  p[0].vy = sqrt(0.25);
  p[0].vz = 0.;

  p[1].x  = 1.;
  p[1].y  = 0.;
  p[1].z  = 0.;
  p[1].vx = 0.;
  p[1].vy = -sqrt(0.25);
  p[1].vz = 0.;

  p[2].x  = 0.5;
  p[2].y  = 0.;
  p[2].z  = 20.;
  p[2].vx = 0.;
  p[2].vy = 0.;
  p[2].vz = -0.2;

  double dt = 0.001;
  double tmax = 10000.;
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

  int n = 0;
  std::cout << std::scientific;
  if ( strcmp(argv[2], "orbit") == 0 ) {
    print_particles(p, std::cout);
    for (t = 0; t < tmax; t+=dt) {
      integrator->step(t, p);
      if(n%100 == 0) print_particles(p, std::cout);
      n += 1;
    }
  } else if ( strcmp(argv[2], "energy") == 0 ) {
    double E = 0.;
    E = 0.5*pow(p[1].v(), 2) + potential(p, 1);
    std::cout << E << "\n";
    for (t = 0; t < tmax; t+=dt) {
      integrator->step(t, p);
      E = 0.5*pow(p[1].v(), 2) + potential(p, 1);
      std::cout << E << "\n";
    }
  } else {
    printf("invalid output kind\n");
    delete integrator;
    exit(1);
  }

  delete integrator;
  return 0;
}
