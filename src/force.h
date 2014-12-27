/**
 * @file
 * @brief Force class
 */

#ifndef FORCE_H_
#define FORCE_H_
#include "particle.h"

/**
 * @typedef ForceFunc
 * @brief function that adds non-gravitational forces
 */
typedef void (*ForceFunc)(Particles&);

class Force {
 public:
  Force();
  ~Force();

  void update_acceleration(Particles &p) const;
  int add_force(ForceFunc force);
 private:
  std::vector<ForceFunc> forces_;
};


#endif  //FORCE_H_
