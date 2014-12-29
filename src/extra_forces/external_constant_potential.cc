#include "external_potential.h"

/** Updates particle acceleration based on a constant force field*/
void external_potential(Particles& particles)
{

  /*Following three variables defines the strength of the force field 
   in each component direction.
   They can be adjusted as desired.*/
  const double force_x = 1.0e26; //in dynes
  const double force_y = 1.0e26; 
  const double force_z = 00.0;
  
  /*Updates the acceleration of each particles*/
  for(unsigned int i = 0; i<particles.size(); ++i)
    {
      particles[i].ax += force_x / particles[i].mass;
      particles[i].ay += force_y / particles[i].mass;
      particles[i].az += force_z / particles[i].mass;
    }
}
