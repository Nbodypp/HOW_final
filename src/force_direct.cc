#include <math.h>
#include "force.h"
#include "constants.h"

Force::Force() {
}

Force::~Force() {
}

/** update acceleration of all particles */
void Force::update_acceleration(Particles &particles) const {
  put_gravity(particles);
  // Now to add non-gravitational forces
  for (auto &f : forces_) {
    f(particles);
  }
}

/** update gravitational acceleration of all particles */
void Force::put_gravity(Particles &p) const {
  // reset acceleration
  for (auto &a : p) {
    a.ax = 0.;
    a.ay = 0.;
    a.az = 0.;
  }
  double r, ax, ay, az;  // temp variables
  for (Particles::size_type i = 0; i < p.size(); i++) {
    r = 0.;
    ax = 0.;
    ay = 0.;
    az = 0.;
    for (Particles::size_type j=i+1; j < p.size(); j++) {
      r = p[i].d(p[j]);
      ax = p[j].mass * (p[j].x - p[i].x) / pow(r, 3);
      ay = p[j].mass * (p[j].y - p[i].y) / pow(r, 3);
      az = p[j].mass * (p[j].z - p[i].z) / pow(r, 3);
      // add to p_i and p_j with different signs
      p[i].ax += ax;
      p[i].ay += ay;
      p[i].az += az;
      p[j].ax -= ax;
      p[j].ay -= ay;
      p[j].az -= az;
    }
    p[i].ax *= G;
    p[i].ay *= G;
    p[i].az *= G;
  }
}

/** add a non-gravitational force */
int Force::add_force(ForceFunc force) {
  forces_.push_back(force);
  return 0;
}

