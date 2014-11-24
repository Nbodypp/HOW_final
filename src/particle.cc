/**
 * @file
 */
#include "particle.h"
#include <stdio.h>
#include <math.h>

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

double Particle::operator-(const Particle& p)
{
  return sqrt(pow((p.x-this->x), 2) +
              pow((p.y-this->y), 2) +
              pow((p.z-this->z), 2));
}

void Particle::print()
{
  printf("%8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
         this->x, this->y, this->z,
         this->vx, this->vy, this->vz,
         this->ax, this->ay, this->az);
}

