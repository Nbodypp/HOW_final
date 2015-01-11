/**
 * @file integrator.h
 * @brief Abstract Integrator class
 */

#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "particle.h"

/**
 * Abstract integrator class.
 */
class Integrator {
 public:
  virtual ~Integrator() {}
  virtual int step(double t, Particles &particles) = 0;
};


#endif  //INTEGRATOR_H_
