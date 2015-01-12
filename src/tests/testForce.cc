#include "catch.hpp"

#include "particle.h"
#include "force.h"
#include <iostream>

// simple drag force for testing additional force
void dragforce(Particles &p) {
  for (Particles::size_type i = 0; i < p.size(); ++i) {
    p[i].ax -= p[i].vx;
    p[i].ay -= p[i].vy;
    p[i].az -= p[i].vz;
  }
}

// Test to make sure that force_direct (which uses
// the Newtonian gravitation formula) works.
TEST_CASE("gravitational force calculation", "[force]") {
  Force force;

  SECTION("two body system") {
    Particle p1, p2;
    p1.mass = 4.;  // at origin
    p2.mass = 1.;
    p2.x = 3.; p2.y = 4.;

    Particles p = {p1, p2};
    force.update_acceleration(p);

    REQUIRE(p[0].mass == 4.);
    REQUIRE(p[1].mass == 1.);
    REQUIRE(p[1].x == 3.);
    REQUIRE(p[1].y == 4.);

    REQUIRE(p[0].ax == 3./125.);
    REQUIRE(p[0].ay == 4./125.);
    REQUIRE(p[1].ax == -3.*4./125.);
    REQUIRE(p[1].ay == -4.*4./125.);

    SECTION("when one is a test particle") {
      p[1].mass = 0.;
      force.update_acceleration(p);

      REQUIRE(p[0].mass == 4.);
      REQUIRE(p[1].mass == 0.);
      REQUIRE(p[1].x == 3.);
      REQUIRE(p[1].y == 4.);

      REQUIRE(p[0].ax == 0.);
      REQUIRE(p[0].ay == 0.);
      REQUIRE(p[1].ax == -3.*4./125.);
      REQUIRE(p[1].ay == -4.*4./125.);
    }
    SECTION("velocity should not affect gravity") {
      p[1].vx = 3212.; p[1].vz = -34.;
      force.update_acceleration(p);

      REQUIRE(p[0].ax == 3./125.);
      REQUIRE(p[0].ay == 4./125.);
      REQUIRE(p[1].ax == -3.*4./125.);
      REQUIRE(p[1].ay == -4.*4./125.);
    }
  }

  SECTION("equal mass particles") {
    Particles particles(2, Particle(2., 1.));
    particles[0].x = 2.0;
    particles[1].x = -2.0;

    force.update_acceleration(particles);

    REQUIRE(particles[0].ax == -0.125);
    REQUIRE(particles[0].ay == 0.0);
    REQUIRE(particles[0].az == 0.0);

    REQUIRE(particles[1].ax == 0.125);
    REQUIRE(particles[1].ay == 0.0);
    REQUIRE(particles[1].az == 0.0);

    Particles particles2(2, Particle(1., 1.));
    particles2[0].x = 3.0;
    particles2[1].y = 4.0;
    force.update_acceleration(particles2);

    REQUIRE(particles2[0].ax == -0.024);
    REQUIRE(particles2[0].ay == 0.032);
    REQUIRE(particles2[0].az == 0.0);

    REQUIRE(particles2[1].ax == 0.024);
    REQUIRE(particles2[1].ay == -0.032);
    REQUIRE(particles2[1].az == 0.0);

    Particles particles3(5, Particle(1., 1.));
    for (int i = 0; i < 5; ++i) {
      particles3[i].x = double(i);
    }

    force.update_acceleration(particles3);

    for(int i=0; i<5; i++) {
        REQUIRE(particles3[i].ay == 0.0);
        REQUIRE(particles3[i].az == 0.0);
    }
    
    REQUIRE( (particles3[0].ax - 1.4236111111111 ) < 0.0000000001);
    REQUIRE( (particles3[1].ax - 0.361111111111111) < 0.0000000001);
    REQUIRE(particles3[2].ax == 0.0);
    REQUIRE( (particles3[3].ax - -0.361111111111111) < 0.0000000001);
    REQUIRE( (particles3[4].ax - -1.4236111111111) < 0.0000000001);
  }
}

TEST_CASE("Test if add_force works", "[force]") {
  // setup the force model
  Force force;
  force.add_force(&dragforce);

  Particles particles;
  particles.push_back(Particle(1, 1));
  particles.back().vx = 3.;
  SECTION("trivial single particle case") {
    force.update_acceleration(particles);
    REQUIRE(particles[0].ax == -3);
  }
  // add another particle to test gravity + dragforce
  particles.push_back(Particle(1, 1));
  particles.back().x = 1.;
  particles.back().vx = 3.;
  SECTION("gravity + additional force") {
    force.update_acceleration(particles);
    REQUIRE(particles[0].ax == -2);
    REQUIRE(particles[1].ax == -4);
  }
}


//Another test seeing if add_force works, this time with
//two extra forces

//Here is an extra force
void extra_force(Particles &particles) {
  for (auto &p : particles) {
    p.ax = p.x;
    p.ay = p.y;
    p.az = p.z;
  }
}

//Here is a second extra force
void extra_force2(Particles &particles) {
  for (auto &p : particles) {
    p.az += 0.1;
  }
}

TEST_CASE("Extra forces","[forcedirect]")
{
  Particles particles(4, Particle(0.,1.));
  particles[0].x = 1.0;
  particles[1].y = 2.0;
  particles[2].z = -2.56;

  Force force;
  force.add_force(&extra_force);
  force.add_force(&extra_force2);
  force.update_acceleration(particles);

  REQUIRE(particles[0].ax == 1.0);
  REQUIRE(particles[0].ay == 0.0);
  REQUIRE(particles[0].az == 0.1);

  REQUIRE(particles[1].ax == 0.0);
  REQUIRE(particles[1].ay == 2.0);
  REQUIRE(particles[1].az == 0.1);

  REQUIRE(particles[2].ax == 0.0);
  REQUIRE(particles[2].ay == 0.0);
  REQUIRE(particles[2].az == -2.46);

  REQUIRE(particles[3].ax == 0.0);
  REQUIRE(particles[3].ay == 0.0);
  REQUIRE(particles[3].az == 0.1);

}
