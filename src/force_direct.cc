#include "force.h"
#include "math.h"

Force::Force() {
}

Force::~Force() {
}

void Force::update_acceleration(const Particles& particles) const
{
  for (int i = 0; i < particles.size(); ++i)
  {
    double r = 0;
    double ax = 0;
    double ay = 0;
    double az = 0;
    for (int j = 0; j < particles.size(); ++j)
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
  }
}
