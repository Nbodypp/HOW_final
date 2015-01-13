/**
 * @file
 *
 * @brief Runge-Kutta 6th order integrator, based on Luther, H. A. "An explicit sixth-order Runge-Kutta formula." Mathematics of Computation (1968): 434-436.
 */

#ifndef RUNGE_KUTTA_SIXTH_H_
#define RUNGE_KUTTA_SIXTH_H_

#include "integrator.h"
#include "force.h"

/**
 * @brief Runge-Kutta 6th order integrator
 */
class RungeKutta6 : public Integrator {
 public:
  RungeKutta6(const double dt, const Force &force);
  ~RungeKutta6();
  int step(double t, Particles &p);
 private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
  Particles k1, k2, k3, k4, k5, k6, k7;   // intermediate states
};

#endif
