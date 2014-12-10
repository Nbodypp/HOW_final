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

  void update_acceleration(const Particles& particles) const;
};


#endif  //FORCE_H_
