/**
 * @file timestep.h
 * @brief Timestep class
 */

#ifndef TIMESTEP_H_
#define TIMESTEP_H_
#include <vector>
#include "particle.h"
#include "integrator.h"

/**
 * @brief Timestep class which dynamically updates the timestep.
 */
class Timestep {
 public:
  Timestep(const double dt_fac);
  ~Timestep();

  double update_timestep(Particles &p, Integrator &integrator) const;
 
 private:
  const double dt_fac;

};


#endif  //TIMESTEP_H_
