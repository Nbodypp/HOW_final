#include "runge-kutta.h"

/**
 * @param dt timestep
 * @param force Force model
 */
RungeKutta4::RungeKutta4(const double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

RungeKutta4::~RungeKutta4()
{}

int RungeKutta4::step(double t, Particles &p) {
  k1 = p;
  force_.update_acceleration(k1);
  k2 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k2[i].x  += k1[i].vx * dt_ * 0.5;
    k2[i].y  += k1[i].vy * dt_ * 0.5;
    k2[i].z  += k1[i].vz * dt_ * 0.5;
    k2[i].vx += k1[i].ax * dt_ * 0.5;
    k2[i].vy += k1[i].ay * dt_ * 0.5;
    k2[i].vz += k1[i].az * dt_ * 0.5;
  }
  force_.update_acceleration(k2);
  k3 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k3[i].x  += k2[i].vx * dt_ * 0.5;
    k3[i].y  += k2[i].vy * dt_ * 0.5;
    k3[i].z  += k2[i].vz * dt_ * 0.5;
    k3[i].vx += k2[i].ax * dt_ * 0.5;
    k3[i].vy += k2[i].ay * dt_ * 0.5;
    k3[i].vz += k2[i].az * dt_ * 0.5;
  }
  force_.update_acceleration(k3);
  k4 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k4[i].x  += k3[i].vx * dt_;
    k4[i].y  += k3[i].vy * dt_;
    k4[i].z  += k3[i].vz * dt_;
    k4[i].vx += k3[i].ax * dt_;
    k4[i].vy += k3[i].ay * dt_;
    k4[i].vz += k3[i].az * dt_;
  }
  force_.update_acceleration(k4);
  // update finally
  for (Particles::size_type i = 0; i < p.size(); ++i) {
    p[i].x  = p[i].x  + (k1[i].vx + 2*k2[i].vx + 2*k3[i].vx + k4[i].vx)/6.*dt_;
    p[i].y  = p[i].y  + (k1[i].vy + 2*k2[i].vy + 2*k3[i].vy + k4[i].vy)/6.*dt_;
    p[i].z  = p[i].z  + (k1[i].vz + 2*k2[i].vz + 2*k3[i].vz + k4[i].vz)/6.*dt_;
    p[i].vx = p[i].vx + (k1[i].ax + 2*k2[i].ax + 2*k3[i].ax + k4[i].ax)/6.*dt_;
    p[i].vy = p[i].vy + (k1[i].ay + 2*k2[i].ay + 2*k3[i].ay + k4[i].ay)/6.*dt_;
    p[i].vz = p[i].vz + (k1[i].az + 2*k2[i].az + 2*k3[i].az + k4[i].az)/6.*dt_;
  }
  return 0;
}
