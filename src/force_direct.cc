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
void Force::put_gravity(Particles &particles) const {
  for (auto &p1 : particles) {
    double r = 0.;
    double ax = 0.;
    double ay = 0.;
    double az = 0.;
    for (auto &p2 : particles) {
      if (&p2 == &p1) {
        continue;
      }
      r = p1.d(p2);
      ax += p2.mass * (p2.x - p1.x) / pow(r, 3);
      ay += p2.mass * (p2.y - p1.y) / pow(r, 3);
      az += p2.mass * (p2.z - p1.z) / pow(r, 3);
    }
    p1.ax = G * ax;
    p1.ay = G * ay;
    p1.az = G * az;
  }
}

/** add a non-gravitational force */
int Force::add_force(ForceFunc force) {
  forces_.push_back(force);
  return 0;
}

