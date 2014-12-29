#include "collision.h"
#include "particle.h"

/** Returns non-zero value if any collision has occured */
int collision_check_all(const Particles& particles)
{
  int has_collision_happened = 0;
  for (auto const &p1 : particles)
  {
    for (auto const &p2 : particles)
    {
      if (&p2 == &p1)
      {
        continue;
      }
      if( p1.radius + p2.radius > p1.d(p2)) 
      {
        has_collision_happened = 1;
      }
    }
  }
  return has_collision_happened;
}
