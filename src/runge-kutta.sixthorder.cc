#include <math.h>
#include "runge-kutta.sixthorder.h"


/**
 * @param dt timestep
 * @param force Force model
 */
RungeKutta6::RungeKutta6(const double dt, const Force &force)
  : dt_(dt),
    force_(force) {
}

RungeKutta6::~RungeKutta6()
{}

int RungeKutta6::step(double t, Particles &p) {
  k1 = p;
  force_.update_acceleration(k1);
  k2 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k2[i].x  += k1[i].vx * dt_;
    k2[i].y  += k1[i].vy * dt_;
    k2[i].z  += k1[i].vz * dt_;
    k2[i].vx += k1[i].ax * dt_;
    k2[i].vy += k1[i].ay * dt_;
    k2[i].vz += k1[i].az * dt_;
  }
  force_.update_acceleration(k2);
  k3 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k3[i].x  += (3*k1[1].vx + k2[i].vx)/8.0 * dt_ * 0.5;
    k3[i].y  += (3*k1[1].vy + k2[i].vy)/8.0 * dt_ * 0.5;
    k3[i].z  += (3*k1[1].vz + k2[i].vz)/8.0 * dt_ * 0.5;
    k3[i].vx += (3*k1[1].ax + k2[i].ax)/8.0 * dt_ * 0.5;
    k3[i].vy += (3*k1[1].ay + k2[i].ay)/8.0 * dt_ * 0.5;
    k3[i].vz += (3*k1[1].az + k2[i].az)/8.0 * dt_ * 0.5;
  }
  force_.update_acceleration(k3);
  k4 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k4[i].x  += (8.*k1[i].vx + 2.*k2[i].vx + 8.*k3[i].vx)/27. * dt_ * 2./3.;
    k4[i].y  += (8.*k1[i].vy + 2.*k2[i].vy + 8.*k3[i].vy)/27. * dt_ * 2./3.;
    k4[i].z  += (8.*k1[i].vz + 2.*k2[i].vz + 8.*k3[i].vz)/27. * dt_ * 2./3.;
    k4[i].vx += (8.*k1[i].ax + 2.*k2[i].ax + 8.*k3[i].ax)/27. * dt_ * 2./3.;
    k4[i].vy += (8.*k1[i].ay + 2.*k2[i].ay + 8.*k3[i].ay)/27. * dt_ * 2./3.;
    k4[i].vz += (8.*k1[i].az + 2.*k2[i].az + 8.*k3[i].az)/27. * dt_ * 2./3.;
  }
  force_.update_acceleration(k4);

  k5 = p;
  double sqrt21 = sqrt(21.);
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k5[i].x  += (3.*(3.*(sqrt21) - 7.)*k1[i].vx - 8.*(7. - sqrt21)*k2[i].vx + 48.*(7. - sqrt21)*k3[i].vx - 3.*(21. - sqrt21)*k4[i].vx)/392. * dt_ * (7. - sqrt21)/14.;
    k5[i].y  += (3.*(3.*(sqrt21) - 7.)*k1[i].vy - 8.*(7. - sqrt21)*k2[i].vy + 48.*(7. - sqrt21)*k3[i].vy - 3.*(21. - sqrt21)*k4[i].vy)/392. * dt_ * (7. - sqrt21)/14.;
    k5[i].z  += (3.*(3.*(sqrt21) - 7.)*k1[i].vz - 8.*(7. - sqrt21)*k2[i].vz + 48.*(7. - sqrt21)*k3[i].vz - 3.*(21. - sqrt21)*k4[i].vz)/392. * dt_ * (7. - sqrt21)/14.;
    k5[i].vx += (3.*(3.*(sqrt21) - 7.)*k1[i].ax - 8.*(7. - sqrt21)*k2[i].ax + 48.*(7. - sqrt21)*k3[i].ax - 3.*(21. - sqrt21)*k4[i].ax)/392. * dt_ * (7. - sqrt21)/14.;
    k5[i].vy += (3.*(3.*(sqrt21) - 7.)*k1[i].ay - 8.*(7. - sqrt21)*k2[i].ay + 48.*(7. - sqrt21)*k3[i].ay - 3.*(21. - sqrt21)*k4[i].ay)/392. * dt_ * (7. - sqrt21)/14.;
    k5[i].vz += (3.*(3.*(sqrt21) - 7.)*k1[i].az - 8.*(7. - sqrt21)*k2[i].az + 48.*(7. - sqrt21)*k3[i].az - 3.*(21. - sqrt21)*k4[i].az)/392. * dt_ * (7. - sqrt21)/14.;
  }
  force_.update_acceleration(k5);


  k6 = p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k6[i].x  += (-5.*(231. + 51.*sqrt21)*k1[i].vx - 40.*(7. + sqrt21)*k2[i].vx - 320.*(sqrt21)*k3[i].vx + 3.*(21. + 121.*sqrt21)*k4[i].vx + 392.*(6. + sqrt21)*k5[i].vx)/1960. * dt_ * (7. + sqrt21)/14.;
    k6[i].y  += (-5.*(231. + 51.*sqrt21)*k1[i].vy - 40.*(7. + sqrt21)*k2[i].vy - 320.*(sqrt21)*k3[i].vy + 3.*(21. + 121.*sqrt21)*k4[i].vy + 392.*(6. + sqrt21)*k5[i].vy)/1960. * dt_ * (7. + sqrt21)/14.;
    k6[i].z  += (-5.*(231. + 51.*sqrt21)*k1[i].vz - 40.*(7. + sqrt21)*k2[i].vz - 320.*(sqrt21)*k3[i].vz + 3.*(21. + 121.*sqrt21)*k4[i].vz + 392.*(6. + sqrt21)*k5[i].vz)/1960. * dt_ * (7. + sqrt21)/14.;
    k6[i].vx += (-5.*(231. + 51.*sqrt21)*k1[i].ax - 40.*(7. + sqrt21)*k2[i].ax - 320.*(sqrt21)*k3[i].ax + 3.*(21. + 121.*sqrt21)*k4[i].ax + 392.*(6. + sqrt21)*k5[i].ax)/1960. * dt_ * (7. + sqrt21)/14.;
    k6[i].vy += (-5.*(231. + 51.*sqrt21)*k1[i].ay - 40.*(7. + sqrt21)*k2[i].ay - 320.*(sqrt21)*k3[i].ay + 3.*(21. + 121.*sqrt21)*k4[i].ay + 392.*(6. + sqrt21)*k5[i].ay)/1960. * dt_ * (7. + sqrt21)/14.;
    k6[i].vz += (-5.*(231. + 51.*sqrt21)*k1[i].az - 40.*(7. + sqrt21)*k2[i].az - 320.*(sqrt21)*k3[i].az + 3.*(21. + 121.*sqrt21)*k4[i].az + 392.*(6. + sqrt21)*k5[i].az)/1960. * dt_ * (7. + sqrt21)/14.;
  }
  force_.update_acceleration(k6);

  k7=p;
  for (Particles::size_type i = 0; i < p.size(); i++) {
    k7[i].x  += (15.*(22. + 7.*sqrt21)*k1[i].vx + 120.*k2[i].vx + 40.*(7.*sqrt21 - 5.)*k3[i].vx - 63.*(3.*sqrt21 - 2.)*k4[i].vx - 14.*(49. + 9.*sqrt21)*k5[i].vx + 70.*(7. - sqrt21)*k6[i].vx)/180. * dt_;
    k7[i].y  += (15.*(22. + 7.*sqrt21)*k1[i].vy + 120.*k2[i].vy + 40.*(7.*sqrt21 - 5.)*k3[i].vy - 63.*(3.*sqrt21 - 2.)*k4[i].vy - 14.*(49. + 9.*sqrt21)*k5[i].vy + 70.*(7. - sqrt21)*k6[i].vy)/180. * dt_;
    k7[i].z  += (15.*(22. + 7.*sqrt21)*k1[i].vz + 120.*k2[i].vz + 40.*(7.*sqrt21 - 5.)*k3[i].vz - 63.*(3.*sqrt21 - 2.)*k4[i].vz - 14.*(49. + 9.*sqrt21)*k5[i].vz + 70.*(7. - sqrt21)*k6[i].vz)/180. * dt_;
    k7[i].vx += (15.*(22. + 7.*sqrt21)*k1[i].ax + 120.*k2[i].ax + 40.*(7.*sqrt21 - 5.)*k3[i].ax - 63.*(3.*sqrt21 - 2.)*k4[i].ax - 14.*(49. + 9.*sqrt21)*k5[i].ax + 70.*(7. - sqrt21)*k6[i].ax)/180. * dt_;
    k7[i].vy += (15.*(22. + 7.*sqrt21)*k1[i].ay + 120.*k2[i].ay + 40.*(7.*sqrt21 - 5.)*k3[i].ay - 63.*(3.*sqrt21 - 2.)*k4[i].ay - 14.*(49. + 9.*sqrt21)*k5[i].ay + 70.*(7. - sqrt21)*k6[i].ay)/180. * dt_;
    k7[i].vz += (15.*(22. + 7.*sqrt21)*k1[i].az + 120.*k2[i].az + 40.*(7.*sqrt21 - 5.)*k3[i].az - 63.*(3.*sqrt21 - 2.)*k4[i].az - 14.*(49. + 9.*sqrt21)*k5[i].az + 70.*(7. - sqrt21)*k6[i].az)/180. * dt_;
  }
  force_.update_acceleration(k7);


  // update finally
  for (Particles::size_type i = 0; i < p.size(); ++i) {
    p[i].x  = p[i].x  + (9.*k1[i].vx + 64.*k3[i].vx + 49.*k5[i].vx + 49.*k6[i].vx + 9.*k7[i].vx)/180.*dt_;
    p[i].y  = p[i].y  + (9.*k1[i].vy + 64.*k3[i].vy + 49.*k5[i].vy + 49.*k6[i].vy + 9.*k7[i].vy)/180.*dt_;
    p[i].z  = p[i].z  + (9.*k1[i].vz + 64.*k3[i].vz + 49.*k5[i].vz + 49.*k6[i].vz + 9.*k7[i].vz)/180.*dt_;
    p[i].vx = p[i].vx + (9.*k1[i].ax + 64.*k3[i].ax + 49.*k5[i].ax + 49.*k6[i].ax + 9.*k7[i].ax)/180.*dt_;
    p[i].vy = p[i].vy + (9.*k1[i].ay + 64.*k3[i].ay + 49.*k5[i].ay + 49.*k6[i].ay + 9.*k7[i].ay)/180.*dt_;
    p[i].vz = p[i].vz + (9.*k1[i].az + 64.*k3[i].az + 49.*k5[i].az + 49.*k6[i].az + 9.*k7[i].az)/180.*dt_;
  }
  return 0;
}
