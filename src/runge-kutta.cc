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
  for (int i = 0; i < k2.size(); ++i)
  {
    k2[i].x  += k2[i].vx * dt_ * 0.5;
    k2[i].y  += k2[i].vy * dt_ * 0.5;
    k2[i].z  += k2[i].vz * dt_ * 0.5;
    k2[i].vx += k2[i].ax * dt_ * 0.5;
    k2[i].vy += k2[i].ay * dt_ * 0.5;
    k2[i].vz += k2[i].az * dt_ * 0.5;
  }
  force_.update_acceleration(k2);
  k3 = k2;
  for (int i = 0; i < k3.size(); ++i)
  {
    k3[i].x  += k3[i].vx * dt_ * 0.5;
    k3[i].y  += k3[i].vy * dt_ * 0.5;
    k3[i].z  += k3[i].vz * dt_ * 0.5;
    k3[i].vx += k3[i].ax * dt_ * 0.5;
    k3[i].vy += k3[i].ay * dt_ * 0.5;
    k3[i].vz += k3[i].az * dt_ * 0.5;
  }
  force_.update_acceleration(k3);
  k4 = k3;
  for (int i = 0; i < k4.size(); ++i)
  {
    k4[i].x  += k4[i].vx * dt_;
    k4[i].y  += k4[i].vy * dt_;
    k4[i].z  += k4[i].vz * dt_;
    k4[i].vx += k4[i].ax * dt_;
    k4[i].vy += k4[i].ay * dt_;
    k4[i].vz += k4[i].az * dt_;
  }
  force_.update_acceleration(k4);
  // update finally
  for (int i = 0; i < p.size(); ++i)
  {
    p[i].x  += k1[i].vx*dt_/6. + (k2[i].vx + k3[i].vx)*dt_/3. + k4[i].vx*dt_/6.;
    p[i].y  += k1[i].vy*dt_/6. + (k2[i].vy + k3[i].vy)*dt_/3. + k4[i].vy*dt_/6.;
    p[i].z  += k1[i].vz*dt_/6. + (k2[i].vz + k3[i].vz)*dt_/3. + k4[i].vz*dt_/6.;
    p[i].vx += k1[i].ax*dt_/6. + (k2[i].ax + k3[i].ax)*dt_/3. + k4[i].ax*dt_/6.;
    p[i].vy += k1[i].ay*dt_/6. + (k2[i].ay + k3[i].ay)*dt_/3. + k4[i].ay*dt_/6.;
    p[i].vz += k1[i].az*dt_/6. + (k2[i].az + k3[i].az)*dt_/3. + k4[i].az*dt_/6.;
  }
  return 0;
}
