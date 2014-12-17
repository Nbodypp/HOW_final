#include "force.h"
#include "math.h"

Force::Force() {
}

Force::~Force() {
}

/** update acceleration of all particles */
void Force::update_acceleration(const Particles& particles, const Extra_Force_Func_Vec &functions) const
{
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    double r = 0.;
    double ax = 0.;
    double ay = 0.;
    double az = 0.;
    for (unsigned int j = 0; j < particles.size(); ++j)
    {
      if (j==i)
      {
        continue;
      }
      r = particles[i]->d((*particles[j]));
      ax += particles[j]->mass * (particles[j]->x - particles[i]->x) / pow(r, 3);
      ay += particles[j]->mass * (particles[j]->y - particles[i]->y) / pow(r, 3);
      az += particles[j]->mass * (particles[j]->z - particles[i]->z) / pow(r, 3);
    }
    particles[i]->ax = ax;
    particles[i]->ay = ay;
    particles[i]->az = az;

    /*Now to add our extra-Newtonian forces and/or corrections*/
    //if(functions != NULL)
    // {
        extra_acceleration(particles,functions);
        // }
  }
}


void Force::extra_acceleration(const Particles& particles, const Extra_Force_Func_Vec &functions) const
{
  double extra_accelerations[particles.size()][3];
  for(unsigned int i=0; i<functions.size(); ++i)
    {
      functions[i](particles,&extra_accelerations);
      
      for(unsigned int j=0; j<particles.size(); ++j)
        {
          particles[j]->ax += extra_accelerations[j][0];
          particles[j]->ay += extra_accelerations[j][1];
          particles[j]->az += extra_accelerations[j][2];
        }
    }
}

