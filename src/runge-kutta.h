/**
 * @file
 *
 * @brief Runge-Kutta 4th order integrator
 */

#ifndef RK4_H_
#define RK4_H_

#include "integrator.h"
#include "force.h"

/**
 * @brief Runge-Kutta 4th order integrator
 */
class RK4 : public Integrator {
 public:
  RK4(double dt,const Force &force);
  ~RK4();
  int step(double t, const Particles& particles);
 private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
  double *k1_, *k2_;	  // RK4 k's
  double *k3_, *k4_;
};

#endif  // RK4_H_
