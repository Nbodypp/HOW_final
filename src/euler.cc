#include "euler.h"

/**
 * @param dt timestep
 * @param foce Force model
 */
Euler::Euler(double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

Euler::~Euler() {
}

/** Step particles' position and velocity */
int Euler::step(double t, const Particles& particles) {

  force_.update_acceleration(particles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    particles[i]->x += dt_ * particles[i]->vx;
    particles[i]->y += dt_ * particles[i]->vy;
    particles[i]->z += dt_ * particles[i]->vz;
    particles[i]->vx += dt_ * particles[i]->ax;
    particles[i]->vy += dt_ * particles[i]->ay;
    particles[i]->vz += dt_ * particles[i]->az;
  }
  return 0;
}
