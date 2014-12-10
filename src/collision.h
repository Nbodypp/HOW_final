/**
 *
 *
 * @brief Collision class, checks if two objects have collided
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include "particle.h"

class Collision {
 public:
  Collision();
  ~Collision();

  int collision_check_all(const Particles& particles) const;
};


#endif  // COLLISION_H_
