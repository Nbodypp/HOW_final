/**
 * @file particle.cc
 * @brief Particle class and related functions
 */

#include "particle.h"
#include "constants.h"
#include <stdio.h>
#include <math.h>
#include <fstream>

/**
 * Default constructor.
 * Mass, radius, position, velocity, and acceleration is all initialized to 0.
 */
Particle::Particle()
  : mass(0),
    radius(0),
    x(0), y(0), z(0),
    vx(0), vy(0), vz(0),
    ax(0), ay(0), az(0)
{}

/**
 * Constructor.
 * Position, velocity, and acceleration is all initialized to 0.
 * @param mass mass of the particle
 * @param radius radius of the particle
 */
Particle::Particle(double mass, double radius)
  : mass(mass),
    radius(radius),
    x(0), y(0), z(0),
    vx(0), vy(0), vz(0),
    ax(0), ay(0), az(0)
{}

/** Destructor */
Particle::~Particle()
{}

/**
 * Calculate the distance between two particles.
 * @param p particle to calculate the distance to
 * @return the distance between this and p
 */
double Particle::d(const Particle& p) const {
  return sqrt(pow((p.x-this->x), 2) +
              pow((p.y-this->y), 2) +
              pow((p.z-this->z), 2));
}

/**
 * Calculate the relative velocity between two particles.
 * @param p particle to calculate the velocity to
 * @return the relative velocity between this and p
 */
double Particle::rv(const Particle& p) const {
  return sqrt(pow((p.vx-this->vx), 2) +
              pow((p.vy-this->vy), 2) +
              pow((p.vz-this->vz), 2));
}

/**
 * Calculate the velocity of the particle.
 * @return velocity
 */
double Particle::v() const {
  return sqrt(pow((this->vx), 2) +
              pow((this->vy), 2) +
              pow((this->vz), 2));
}

/**
 * Calculate the kinetic energy of the particle.
 * @return kinetic energy
 */
double Particle::Ekin() const {
  return 0.5 * this->mass * pow(this->v(), 2);
}

/**
 * Print position, velocity, and acceleration of the particle
 */
void Particle::print() {
  printf("%15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e %15.8e\n",
         this->x, this->y, this->z,
         this->vx, this->vy, this->vz,
         this->ax, this->ay, this->az);
}

/**
 * Print formatted position, velocity and acceleration of all particles
 * @param particles particles
 * @param f output stream
 */
void print_particles(const Particles &particles, std::ostream &f) {
  for (const auto &p : particles) {
    f << std::scientific;
    f << p.x << ' '
      << p.y << ' '
      << p.z << ' '
      << p.vx << ' '
      << p.vy << ' '
      << p.vz << ' '
      << p.ax << ' '
      << p.ay << ' '
      << p.az << ' ';
  }
  f << '\n';
}

/**
 * Save position, velocity of all particles in a binary format
 * For each time step, x, y, z, vx, vy, vz of each particle is stored
 * as double.
 * @param particles particles to save
 * @param f binary output stream
 */
void save_particles(const Particles &particles, std::ofstream &f) {
  double buf[6];
  for (const auto &p : particles) {
    buf[0] = p.x;
    buf[1] = p.y;
    buf[2] = p.z;
    buf[3] = p.vx;
    buf[4] = p.vy;
    buf[5] = p.vz;
    f.write((char*)&buf, sizeof(buf));
  }
}

/**
 * Calculate the potential of particle i given the configuration
 * @param particles Particles
 * @param i zero-based index of the particle
 * @return potential energy of particle i
 */
double potential(const Particles& particles, const Particles::size_type i) {
  double E = 0;
  for (Particles::size_type j = 0; j < particles.size(); ++j) {
    if (j == i) {
      continue;
    }
    E += -G * particles[j].mass / particles[j].d(particles[i]);
  }
  return E;
}

