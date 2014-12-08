#include "euler.h"
#include "force.h"

Euler::Euler(double dt, int Nparticles)
  : dt_(dt),
    Nparticles_(Nparticles) {
  x_ = new double[3*Nparticles_];
  v_ = new double[3*Nparticles_];
  a_ = new double[3*Nparticles_];
}

Euler::~Euler() {
  delete [] x_;
  delete [] v_;
  delete [] a_;
}

int Euler::step(double t, const Particles& particles) {
  update_acceleration(particles);
  for (int i = 0; i < Nparticles_; ++i)
  {
    x_[i*3]   = particles[i]->x;
    x_[i*3+1] = particles[i]->y;
    x_[i*3+2] = particles[i]->z;
    v_[i*3]   = particles[i]->vx;
    v_[i*3+1] = particles[i]->vy;
    v_[i*3+2] = particles[i]->vz;
    a_[i*3]   = particles[i]->ax;
    a_[i*3+1] = particles[i]->ay;
    a_[i*3+2] = particles[i]->az;
  }

  for (int i = 0; i < 3*Nparticles_; ++i)
  {
    x_[i] += dt_ * v_[i];
    v_[i] += dt_ * a_[i];
  }
  for (int i = 0; i < Nparticles_; ++i)
  {
    particles[i]->x = x_[i*3];
    particles[i]->y = x_[i*3+1];
    particles[i]->z = x_[i*3+2];
    particles[i]->vx = v_[i*3];
    particles[i]->vy = v_[i*3+1];
    particles[i]->vz = v_[i*3+2];
    particles[i]->ax = a_[i*3];
    particles[i]->ay = a_[i*3+1];
    particles[i]->az = a_[i*3+2];
  }
  return 0;
}
