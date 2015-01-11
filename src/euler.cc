/**
 * @file euler.cc
 * @brief Forward Euler integrator
 */

#include "euler.h"

/**
 * Constructor.
 * @param dt timestep
 * @param force Force model
 */
Euler::Euler(double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

Euler::~Euler() {
}

/**
 * Inegrate particles' position and velocity for one time step.
 */
int Euler::step(double t, Particles &particles) {
  force_.update_acceleration(particles);
  for (auto &p : particles) {
    p.x  += dt_ * p.vx;
    p.y  += dt_ * p.vy;
    p.z  += dt_ * p.vz;
    p.vx += dt_ * p.ax;
    p.vy += dt_ * p.ay;
    p.vz += dt_ * p.az;
  }
  return 0;
}
