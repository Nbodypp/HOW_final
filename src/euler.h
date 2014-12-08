#ifndef EULER_H_
#define EULER_H_

#include "particle.h"

class Euler {
 public:
   Euler(double dt, int Nparticles);  // TODO: seems better to accept force model
   ~Euler();
   int step(double t, const Particles& particles);
 private:
   const double dt_;    // timestep
   const int Nparticles_;
   double* x_;
   double* v_;
   double* a_;
};
#endif  // EULER_H_
