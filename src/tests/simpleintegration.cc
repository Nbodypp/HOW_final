/* This file defines a simple force to integrate
 * for the purpose of testing the integrators.
 * The function defined here has a simple analytic
 * form for the trajectories of both position and velocity
 */

#include "simpleintegration.h"

void SimpleIntegration(Particles &particles){
  for (auto &p : particles) {
    p.ax = ax_0;
    p.ay = ay_0;
    p.az = az_0;
  }
}
