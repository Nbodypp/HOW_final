/**
 * @file
 * @brief Force class
 */

#ifndef FORCE_H_
#define FORCE_H_
#include "particle.h"

class Force {
 public:
  Force();
  ~Force();

  /**
   * update acceleration of all particles
   * @param particles instance of Particles
   */
  void update_acceleration(const Particles& particles) const;
};


#endif  //FORCE_H_
