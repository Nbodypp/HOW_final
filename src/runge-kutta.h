/**
 * @file
 *
 * @brief Runge-Kutta 4th order integrator
 */

#ifndef RUNGE_KUTTA_H_
#define RUNGE_KUTTA_H_

#include "integrator.h"
#include "force.h"

/**
 * @brief Runge-Kutta 4th order integrator
 */
class RungeKutta4 : public Integrator {
 public:
  RungeKutta4(const double dt, const Force &force);
  ~RungeKutta4();
  int step(double t, Particles &p);
 private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
  Particles k1, k2, k3, k4;   // intermediate states
};

#endif
