#include <cmath>
#include "timestep.h"
#include "integrator.h"

/** 
 * Constructor 
 * @param dt_fac factor to scale the timestep
 */
Timestep::Timestep(const double dt_fac) 
  : dt_fac(dt_fac)
{}

/** Destructor **/
Timestep::~Timestep() {
}

/**
 * Update (global) timestep
 */
double Timestep::update_timestep(Particles &p, Integrator &integrator) const {
  double r, rv, drdv, tempdrdv;  
  drdv = INFINITY;
  for (auto i = p.begin(); i != p.end(); ++i) {
    r = 0.;
    rv = 0.;
    tempdrdv = INFINITY;
    for (auto j = i+1; j != p.end(); ++j) {
      r = i->d(*j);
      rv = i->rv(*j);
      if (rv==0) {
	rv = 1.;
      }
      tempdrdv = fabs(r/rv);
      if (tempdrdv < drdv) {
        drdv = tempdrdv;
      }
    }
  }
  integrator.update_dt((this->dt_fac)*drdv); 
  return (this->dt_fac)*drdv;
}
