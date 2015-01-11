/**
 * @file force.h
 * @brief Force class
 */

#ifndef FORCE_H_
#define FORCE_H_
#include <vector>
#include "particle.h"

/**
 * @typedef ForceFunc
 * @brief function that adds non-gravitational forces to Particles
 */
typedef void (*ForceFunc)(Particles&);

/**
 * @brief Force class to set up force model.
 * This class sets up force model for the problem. Gravity is included by
 * default, and additional forces may be added.
 * @see ForceFunc
 */
class Force {
 public:
  Force();
  ~Force();

  void update_acceleration(Particles &p) const;
  void put_gravity(Particles &p) const;
  int add_force(ForceFunc force);
 private:
  std::vector<ForceFunc> forces_;
};


#endif  //FORCE_H_
