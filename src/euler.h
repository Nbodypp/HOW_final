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
