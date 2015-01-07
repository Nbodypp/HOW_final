#include "collision.h"
#include "particle.h"

/** Returns non-zero value if any collision has occured */
int collision_check_all(const Particles& particles) {
  int has_collision_happened = 0; 
  double r;
  for (Particles::size_type i = 0; i < particles.size(); ++i) {
    for (Particles::size_type j = 0; j < i; ++j) {
      r = particles[i].d((particles[j]));
      if ( (particles[i].radius + particles[j].radius) > r ) {
        has_collision_happened = 1;
      }
    }
  }
  return has_collision_happened;
}
