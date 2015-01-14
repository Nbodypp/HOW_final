/**
 * @file euler.h
 * @brief Forward Euler integrator
 */

#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "force.h"

/**
 * Forward Euler integrator.
 */
class Euler : public Integrator {
 public:
  Euler(double dt, const Force &force);
  ~Euler();
  int step(double t, Particles &particles);
  int update_dt(double dt);
 private:
  double dt_;       // timestep
  const Force &force_;    // Force model
};

#endif  // EULER_H_

