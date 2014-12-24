#include "rk4.h"
#include "particles.h"

/**
 * @param dt timestep
 * @param force Force model
 */
RK4::RK4(double dt, const Force &force, const int np)
  : dt_(dt),
    force_(force) 
    np_(np)	 {
  k1_ = new double[np_][6];
  k2_ = new double[np_][6];
  k3_ = new double[np_][6];
  k4_ = new double[np_][6];
}

RK4::~RK4() {
  delete k1_; 
  delete k2_; 
  delete k3_; 
  delete k4_; 
}

/** Step particles' position and velocity */
int RK4::step(double t, const Particles& particles) {
  Particles tempparticles; 
  force_.update_acceleration(particles);
  tempparticles = particles; //Not sure if this is valid

  //Calculate k1 for all particles and dimensions
  //Update tempparticles in preparation for k2
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    k1_[i][1] = particles[i]->vx;
    tempparticles[i]->x += 0.5*k1_[i][1];

    k1_[i][2] = particles[i]->vy;
    tempparticles[i]->y += 0.5*k1_[i][2];

    k1_[i][3] = particles[i]->vz;
    tempparticles[i]->z += 0.5*k1_[i][3];

    k1_[i][4] = particles[i]->ax;
    tempparticles[i]->vx += 0.5*k1_[i][4];

    k1_[i][5] = particles[i]->ay;
    tempparticles[i]->vy += 0.5*k1_[i][5];

    k1_[i][6] = particles[i]->az;
    tempparticles[i]->vz += 0.5*k1_[i][6];
  }

  //Calculate k2 for all particles and dimensions
  //Update tempparticles in preparation for k3
  force_.update_acceleration(tempparticles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    k2_[i][1] = particles[i]->vx + 0.5*dt_*k1_[i][1];
    tempparticles[i]->x = particles->x + 0.5*dt_*k2_[i][1];

    k2_[i][2] = particles[i]->vy + 0.5*dt_*k1_[i][2];
    tempparticles[i]->y = particles->y + 0.5*dt_*k2_[i][2];

    k2_[i][3] = particles[i]->vz + 0.5*dt_*k1_[i][3];
    tempparticles[i]->z = particles->z + 0.5*dt_*k2_[i][3];

    k2_[i][4] = tempparticles[i]->ax;
    tempparticles[i]->vx = particles->vx + 0.5*dt_*k2_[i][4];

    k2_[i][5] = tempparticles[i]->ay;
    tempparticles[i]->vy = particles->vy + 0.5*dt_*k2_[i][5];

    k2_[i][6] = tempparticles[i]->az;
    tempparticles[i]->vz = particles->vz + 0.5*dt_*k2_[i][6];
  }

  //Calculate k3 for all particles and dimensions
  //Update tempparticles in preparation for k4
  force_.update_acceleration(tempparticles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    k3_[i][1] = particles[i]->vx + 0.5*dt_*k2_[i][1];
    tempparticles[i]->x = particles->x + dt_*k3_[i][1];

    k3_[i][2] = particles[i]->vy + 0.5*dt_*k2_[i][2];
    tempparticles[i]->y = particles->y + dt_*k3_[i][2];

    k3_[i][3] = particles[i]->vz + 0.5*dt_*k2_[i][3];
    tempparticles[i]->z = particles->z + dt_*k3_[i][3];

    k3_[i][4] = tempparticles[i]->ax;
    tempparticles[i]->vx = particles->vx + dt_*k3_[i][4];

    k3_[i][5] = tempparticles[i]->ay;
    tempparticles[i]->vy = particles->vy + dt_*k3_[i][5];

    k3_[i][6] = tempparticles[i]->az;
    tempparticles[i]->vz = particles->vz + dt_*k3_[i][6];
  }

  //Calculate k4 for all particles and dimensions
  force_.update_acceleration(tempparticles);
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    k4_[i][1] = particles[i]->vx + dt_*k3_[i][1];
    k4_[i][2] = particles[i]->vy + dt_*k3_[i][2];
    k4_[i][3] = particles[i]->vz + dt_*k3_[i][3];
    k4_[i][4] = tempparticles[i]->ax;
    k4_[i][5] = tempparticles[i]->ay;
    k4_[i][6] = tempparticles[i]->az;
  }

  //Update all particles using k's
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    particles[i]->x += dt_ * (k1_[i][1]/6 + (k2_[i][1]+k3_[i][1])/3 + k4_[i][1]/6);
    particles[i]->y += dt_ * (k1_[i][2]/6 + (k2_[i][2]+k3_[i][2])/3 + k4_[i][2]/6)
    particles[i]->z += dt_ * (k1_[i][3]/6 + (k2_[i][3]+k3_[i][3])/3 + k4_[i][3]/6)
    particles[i]->vx += dt_ * (k1_[i][4]/6 + (k2_[i][4]+k3_[i][5])/3 + k4_[i][4]/6)
    particles[i]->vy += dt_ * (k1_[i][5]/6 + (k2_[i][5]+k3_[i][5])/3 + k4_[i][5]/6)
    particles[i]->vz += dt_ * (k1_[i][6]/6 + (k2_[i][6]+k3_[i][6])/3 + k4_[i][6]/6)
  }

  return 0;
}
