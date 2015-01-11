#include <math.h>
#include "force.h"
#include "constants.h"

/** Constructor */
Force::Force() {
}

/** Destructor */
Force::~Force() {
}

/**
 * Update acceleration of all particles.
 * When called, ax, ay, az values of all particles are updated including any
 * non-gravitational force that may have been added.
 * @param particles Particles
 * @see add_force
 */
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
  for (auto i = p.begin(); i != p.end(); ++i) {
    r = 0.;
    ax = 0.;
    ay = 0.;
    az = 0.;
    for (auto j = i+1; j != p.end(); ++j) {
      r = i->d(*j);
      ax = j->mass * (j->x - i->x) / pow(r, 3);
      ay = j->mass * (j->y - i->y) / pow(r, 3);
      az = j->mass * (j->z - i->z) / pow(r, 3);
      // add to p_i and p_j with different signs
      i->ax += ax;
      i->ay += ay;
      i->az += az;
      j->ax -= ax;
      j->ay -= ay;
      j->az -= az;
    }
    i->ax *= G;
    i->ay *= G;
    i->az *= G;
  }
}

/**
 * Add a non-gravitational force function.
 * @see ForceFunc
 */
int Force::add_force(ForceFunc force) {
  forces_.push_back(force);
  return 0;
}

