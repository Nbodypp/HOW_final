/**
 * @file
 *
 * @brief Leapfrog integrator class
 * Longer description goes here
 */

#ifndef LEAPFROG_H_
#define LEAPFROG_H_

#include "integrator.h"
#include "force.h"

class Leapfrog : public Integrator
{
public:
  Leapfrog(double dt, const Force &force);
  ~Leapfrog();
  int step(double t, Particles &particles);
private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
  void advance_vel(double dt, Particles &particles);
  
};

#endif  // LEAPFROG_H_
