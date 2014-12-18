#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "particle.h"
#include "force.h"

void dragforce(const Particles &p) {
  for (int i = 0; i < p.size(); ++i)
  {
    p[i]->ax -= p[i]->vx;
    p[i]->ay -= p[i]->vy;
    p[i]->az -= p[i]->vz;
  }
};

TEST_CASE("Create Particle", "[particle]") {
  Particles particles;
  particles.push_back(std::unique_ptr<Particle>(new Particle(1, 1)));
  particles.back()->vx = 3.;

  Force force;

  force.add_force(dragforce);
  force.update_acceleration(particles);
  print_particles(particles);
  REQUIRE(particles[0]->ax == -3);
}
