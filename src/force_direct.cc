#include "force.h"
#include "math.h"
#include "constants.h"

Force::Force() {
}

Force::~Force() {
}

/** update acceleration of all particles */
void Force::update_acceleration(Particles &particles) const
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
      r = particles[i].d(particles[j]);
      ax += particles[j].mass * (particles[j].x - particles[i].x) / pow(r, 3);
      ay += particles[j].mass * (particles[j].y - particles[i].y) / pow(r, 3);
      az += particles[j].mass * (particles[j].z - particles[i].z) / pow(r, 3);
    }
    particles[i].ax = G * ax;
    particles[i].ay = G * ay;
    particles[i].az = G * az;

    // Now to add our non-gravitational forces
    for (int i = 0; i < forces_.size(); ++i)
    {
      forces_[i](particles);
    }
  }
}

/** add a non-gravitational force*/
int Force::add_force(ForceFunc force) {
  forces_.push_back(force);
  return 0;
}

