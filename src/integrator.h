#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_
#include "particle.h"

class Integrator {
 public:
   virtual ~Integrator() {}
   virtual int Step(double dt, const Particle& particle);
}


#endif  //INTEGRATOR_H_
