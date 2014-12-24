#include "leapfrog.h"

Leapfrog::Leapfrog(double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

Leapfrog::~Leapfrog() {
}

int Leapfrog::step(double t, Particles& particles) {

  force_.update_acceleration(particles);
  advance_vel(0.5*dt_, particles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    particles[i].x += dt_ * particles[i].vx;
    particles[i].y += dt_ * particles[i].vy;
    particles[i].z += dt_ * particles[i].vz;
  }
  force_.update_acceleration(particles);
  advance_vel(0.5*dt_, particles);  // sync vel with position
  return 0;
}

// advance velocity by dt
void Leapfrog::advance_vel(double dt, Particles& particles) {
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    particles[i].vx += dt * particles[i].ax;
    particles[i].vy += dt * particles[i].ay;
    particles[i].vz += dt * particles[i].az;
  }
}
