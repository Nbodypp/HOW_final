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
int Euler_SI::step(double t, const Particles& particles) {

  force_.update_acceleration(particles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    //Calculate velocity
    particles[i]->vx += dt_ * particles[i]->ax;
    particles[i]->vy += dt_ * particles[i]->ay;
    particles[i]->vz += dt_ * particles[i]->az;

    //Calculate position using new, updated velocity
    particles[i]->x += dt_ * particles[i]->vx;
    particles[i]->y += dt_ * particles[i]->vy;
    particles[i]->z += dt_ * particles[i]->vz;

  }
  return 0;
}
