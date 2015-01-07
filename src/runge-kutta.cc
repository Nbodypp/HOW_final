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
  k2 = k1;
  for (auto &ptmp : k2) {
    ptmp.x  += ptmp.vx * dt_ * 0.5;
    ptmp.y  += ptmp.vy * dt_ * 0.5;
    ptmp.z  += ptmp.vz * dt_ * 0.5;
    ptmp.vx += ptmp.ax * dt_ * 0.5;
    ptmp.vy += ptmp.ay * dt_ * 0.5;
    ptmp.vz += ptmp.az * dt_ * 0.5;
  }
  force_.update_acceleration(k2);
  k3 = k2;
  for (auto &ptmp : k3) {
    ptmp.x  += ptmp.vx * dt_ * 0.5;
    ptmp.y  += ptmp.vy * dt_ * 0.5;
    ptmp.z  += ptmp.vz * dt_ * 0.5;
    ptmp.vx += ptmp.ax * dt_ * 0.5;
    ptmp.vy += ptmp.ay * dt_ * 0.5;
    ptmp.vz += ptmp.az * dt_ * 0.5;
  }
  force_.update_acceleration(k3);
  k4 = k3;
  for (auto &ptmp : k4) {
    ptmp.x  += ptmp.vx * dt_;
    ptmp.y  += ptmp.vy * dt_;
    ptmp.z  += ptmp.vz * dt_;
    ptmp.vx += ptmp.ax * dt_;
    ptmp.vy += ptmp.ay * dt_;
    ptmp.vz += ptmp.az * dt_;
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
