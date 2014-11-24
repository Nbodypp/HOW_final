/**
 * @file
 */
#include "particle.h"
#include <stdio.h>

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


void Particle::print()
{
  printf("%15.8f %15.8f %15.8f %15.8f %15.8f\n",
         this->mass, this->radius, this->x, this->y, this->z);
}

