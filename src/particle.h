/**
 * @file particle.h
 * @brief Particle class and related functions
 *
 * This file contains Particle class, Particles typedef, and related functions
 * that calculates quantities from particles' state or outputs particles' state
 * for further analysis.
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include <memory>
#include <fstream>

/**
 * @brief Particle class for each body.
 * Particle class represents each particle in the simulation. Zero-mass
 * particles are test particles that exerts no force on any other particles.
 * Radius is only relevant when collision is checked. When first instantiated,
 * the initial conditions of position (x, y, z), and velocity (vx, vy, vz)
 * should be specified.
 * @see Particles
 */
class Particle {
 public:
  Particle();
  Particle(double mass, double radius);
  ~Particle();

  double mass;    /**< mass of the particle */
  double radius;  /**< radius of the particle */

  double x;  /**< position x */
  double y;  /**< position y */
  double z;  /**< position z */

  double vx;  /**< velocity x */
  double vy;  /**< velocity y */
  double vz;  /**< velocity z */

  double ax;  /**< acceleration x */
  double ay;  /**< acceleration y */
  double az;  /**< acceleration z */

  void print();
  double d(const Particle &particle) const;
  double rv(const Particle &particle) const;
  double v() const;
  double Ekin() const;

 private:
  static const int dimen_ = 3;
};

/**
 * @typedef Particles
 * @brief vector of Particles
 */
typedef std::vector<Particle> Particles;

void print_particles(const Particles &particles, const double t, const double dt, std::ostream &f);
void save_particles(const Particles &particles, std::ofstream &f);
double potential(const Particles &particles, const Particles::size_type i);

#endif  // PARTICLE_H_

