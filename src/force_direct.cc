#include <math.h>
#include "force.h"
#include "constants.h"

/** Constructor */
Force::Force(int gravity/*=1*/)
  : gravity_(gravity) {
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
  if (gravity_) {
    put_gravity(particles);
  }
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
  double r, dax, day, daz;  // temp vdaridables
  for (auto i = p.begin(); i != p.end(); ++i) {
    r = 0.;
    dax = 0.;
    day = 0.;
    daz = 0.;
    for (auto j = i+1; j != p.end(); ++j) {
      r = i->d(*j);
      dax = (j->x - i->x) / pow(r, 3);
      day = (j->y - i->y) / pow(r, 3);
      daz = (j->z - i->z) / pow(r, 3);
      // add to p_i and p_j with different signs
      i->ax += j->mass * dax;
      i->ay += j->mass * day;
      i->az += j->mass * daz;
      j->ax -= i->mass * dax;
      j->ay -= i->mass * day;
      j->az -= i->mass * daz;
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

