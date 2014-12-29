#include "external_potential.h"
#include "math.h"
#include "../constants.h"

/** Updates particle acceleration based on a central force field*/
void external_potential(Particles& particles)
{

  /*Central location of the force field*/
  const double central_location[3] = {0.0,0.0,0.0};

  /*The "mass" of the imaginary object located at the central 
   location of the force field.  Used to define field strength.*/
  const double central_pseudo_mass = 1.;
  
  /*Updates the acceleration of each particles*/
  for(unsigned int i = 0; i<particles.size(); ++i)
    {
      const double r = sqrt( (particles[i].x - central_location[0])*(particles[i].x - central_location[0]) + (particles[i].y - central_location[1])*(particles[i].y - central_location[1]) + (particles[i].z - central_location[2])*(particles[i].z - central_location[2]) );
      
      particles[i].ax += G * central_pseudo_mass * (particles[i].x - central_location[0]) / pow(r, 3);
      particles[i].ay += G * central_pseudo_mass * (particles[i].y - central_location[1]) / pow(r, 3);
      particles[i].az += G * central_pseudo_mass * (particles[i].z - central_location[2]) / pow(r, 3);
    }
}
