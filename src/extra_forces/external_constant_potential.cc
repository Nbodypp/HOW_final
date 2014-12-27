#include "external_potential.h"

void external_potential(Particles& particles)
{

  const double force_x = 1.0e26; //in dynes
  const double force_y = 1.0e26; 
  const double force_z = 00.0;
  
  for(unsigned int i = 0; i<particles.size(); ++i)
    {
      particles[i].ax += force_x / particles[i].mass;
      particles[i].ay += force_y / particles[i].mass;
      particles[i].az += force_z / particles[i].mass;
    }
}
