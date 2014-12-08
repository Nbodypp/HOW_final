#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "force.h"

class Euler : public Integrator {
 public:
  Euler(double dt, int Nparticles, const Force &force);
  ~Euler();
  int step(double t, const Particles& particles);
 private:
  const double dt_;       // timestep
  const int Nparticles_;  // number of particles
  const Force &force_;    // Force model
  double* x_;             // space for position array
  double* v_;             // space for velocity array
  double* a_;             // space for acceleration array
};

#endif  // EULER_H_
