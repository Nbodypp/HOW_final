/**
 * @file
 */
#include "particle.h"
#include <stdio.h>

Particle::Particle(double mass, double radius)
 : mass(mass),
   radius(radius)
{}


Particle::~Particle()
{}


void Particle::print()
{
  printf("%15.8f %15.8f %15.8f %15.8f %15.8f\n",
         this->mass, this->radius, this->x, this->y, this->z);
}

