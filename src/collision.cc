#include <stdio.h>
#include <vector>
#include "collision.h"
#include "particle.h"

Collision::Collision() {
}

Collision::~Collision() {
}

/** Checks all particles to see if a collision has occured */
int Collision::collision_check_all(const Particles& particles) const
{
  int has_collision_happened = 0; ///< Keeps track of whether a collision happened.  0 for no, nonzero for yes
  double r;

  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    for (unsigned int j = 0; j < i; ++j)
    {
      r = particles[i]->d((*particles[j]));

      if( (particles[i]->radius + particles[j]->radius) < r) //If they are closer than their summed radii
        {
          has_collision_happened = 1;
          printf("#COLLISION OCCURRED!\n");
        }
    }
  }

  return has_collision_happened;
}
