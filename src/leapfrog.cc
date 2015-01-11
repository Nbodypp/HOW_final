/**
 * @file leapfrog.cc
 * @brief Forward Euler integrator
 */

#include "leapfrog.h"

/**
 * Constructor.
 * @param dt timestep
 * @param force Force model
 */
Leapfrog::Leapfrog(double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

Leapfrog::~Leapfrog() {
}

/**
 * Inegrate particles' position and velocity for one time step.
 */
int Leapfrog::step(double t, Particles& particles) {

  force_.update_acceleration(particles);
  advance_vel(0.5*dt_, particles);
  for (auto &ptmp : particles) {
    ptmp.x += dt_ * ptmp.vx;
    ptmp.y += dt_ * ptmp.vy;
    ptmp.z += dt_ * ptmp.vz;
  }
  force_.update_acceleration(particles);
  advance_vel(0.5*dt_, particles);  // sync vel with position
  return 0;
}

// advance velocity by dt
void Leapfrog::advance_vel(double dt, Particles& particles) {
  for (auto &ptmp : particles) {
    ptmp.vx += dt * ptmp.ax;
    ptmp.vy += dt * ptmp.ay;
    ptmp.vz += dt * ptmp.az;
  }
}
