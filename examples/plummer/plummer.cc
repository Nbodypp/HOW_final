#include <iostream>
#include <random>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"

double G = 1;

// Generate plummer sphere of M=1, R=1
// Reference: http://adsabs.harvard.edu/abs/1974A%26A....37..183A
void generate_plummer_sphere(Particles &ps) {
  // make a dice
  std::default_random_engine generator;
  std::uniform_real_distribution<double> dist(0, 1);
  auto dice = std::bind(dist, generator);

  float N = ps.size();  // number of particles
  double X1, X2, X3, X4, gX4, X5, X6, X7;
  double V, Ve;
  double r, x, y, z, u, v, w;
  for (auto& p : ps) {
    p.mass = 1.0 / N;
    X1 = dice();
    X2 = dice();
    X3 = dice();
    r = pow(pow(X1, -2./3.)-1., -0.5);
    z = (1. - 2. * X2) * r;
    x = pow(pow(r, 2) - pow(z, 2), 0.5) * cos(2*M_PI*X3);
    y = pow(pow(r, 2) - pow(z, 2), 0.5) * sin(2*M_PI*X3);
    p.x = x;
    p.y = y;
    p.z = z;
    Ve = sqrt(2.) * pow((1.+pow(r, 2)), -0.25);
    X4 = dice();
    X5 = dice();
    gX4 = pow(X4, 2) * pow(1.-pow(X4, 2), 3.5);
    while (0.1*X5 >= gX4) {
      X4 = dice();
      X5 = dice();
      gX4 = pow(X4, 2) * pow(1.-pow(X4, 2), 3.5);
    }
    V = Ve * X4;
    X6 = dice();
    X7 = dice();
    w = (1.-2.*X6) * V;
    u = pow(pow(V, 2)-pow(w, 2), 0.5) * cos(2*M_PI*X7);
    v = pow(pow(V, 2)-pow(w, 2), 0.5) * sin(2*M_PI*X7);
    p.vx = u;
    p.vy = v;
    p.vz = w;
  }
}

int main(int argc, char *argv[]) {

  Particles p(100, Particle(0, 0));
  generate_plummer_sphere(p);

  double dt = 1e-4;
  double t = 0;
  double tmax = 10.;

  Force force;
  Leapfrog integrator(dt, force);
  print_particles(p, std::cout);
  int i = 1;
  for (t = 0; t < tmax; t+=dt) {
    integrator.step(t, p);
    if (i % 10 == 0) {
      print_particles(p, std::cout);
    }
    i++;
  }
  return 0;
}
