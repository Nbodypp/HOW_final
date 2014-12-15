/**
 * @file
 *
 * @brief Semi Implicit Euler integrator
 */

#ifndef EULER_SI_H_
#define EULER_SI_H_

#include "integrator.h"
#include "force.h"

/**
 * @brief Semi Implicit Euler integrator
 */
class Euler_SI : public Integrator {
 public:
  Euler_SI(double dt,const Force &force);
  ~Euler_SI();
  int step(double t, const Particles& particles);
 private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
};

#endif  // EULER_SI_H_
