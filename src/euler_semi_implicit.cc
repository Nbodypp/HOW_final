#include "euler_semi_implicit.h"

/**
 * @param dt timestep
 * @param foce Force model
 */
Euler_SI::Euler_SI(double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

Euler_SI::~Euler_SI() {
}

/** Step particles' position and velocity */
int Euler_SI::step(double t, Particles& particles) {

  force_.update_acceleration(particles);
  for (auto &p : particles)
  {
    //Calculate velocity
    p.vx += dt_ * p.ax;
    p.vy += dt_ * p.ay;
    p.vz += dt_ * p.az;
    //Calculate position using new, updated velocity
    p.x += dt_ * p.vx;
    p.y += dt_ * p.vy;
    p.z += dt_ * p.vz;
  }
  return 0;
}
