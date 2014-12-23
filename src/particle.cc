#include "particle.h"
#include <stdio.h>
#include <math.h>

/**
 * Constructor
 * @param mass mass of the particle
 * @param radius radius of the particle
 */
Particle::Particle(double mass, double radius)
 : mass(mass),
   radius(radius),
   x(0), y(0), z(0),
   vx(0), vy(0), vz(0),
   ax(0), ay(0), az(0)
{
}


Particle::~Particle()
{}

/** distance between particles */
double Particle::d(const Particle& p)
{
  return sqrt(pow((p.x-this->x), 2) +
              pow((p.y-this->y), 2) +
              pow((p.z-this->z), 2));
}

/** velocity of the particle */
double Particle::v() {
  return sqrt(pow((this->vx), 2) +
              pow((this->vy), 2) +
              pow((this->vz), 2));
}

/** Kinetic energy of the particle */
double Particle::Ekin() {
  return 0.5 * this->mass * pow(this->v(), 2);
}

/** print position, velocity, and acceleration of the particle */
void Particle::print()
{
  printf("%15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e\n",
         this->x, this->y, this->z,
         this->vx, this->vy, this->vz,
         this->ax, this->ay, this->az);
}

/** print position, velocity and acceleration of all particles */
void print_particles(const Particles &particles) {
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    printf("%15.4e %15.4e %15.4e %15.4e %15.4e %15.4e %15.4e %15.4e %15.4e",
        particles[i]->x,
        particles[i]->y,
        particles[i]->z,
        particles[i]->vx,
        particles[i]->vy,
        particles[i]->vz,
        particles[i]->ax,
        particles[i]->ay,
        particles[i]->az);
  }
  printf("\n");
}

/** calculate the kinetic energy of the particle */
double kinetic_energy(const Particles& particles) {
  double E = 0;
  for (unsigned int i = 0; i < particles.size(); ++i)
  {
    E += particles[i]->Ekin();
  }
  return E;
}

/** calculate the potential energy of particles configuration */
double potential_energy(const Particles& particles) {
  double E = 0;
  // TODO
  return E;
}

