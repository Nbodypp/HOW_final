/**
 * @file
 *
 * @brief Particle class
 * Longer description goes here
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include <memory>

/**
 * @brief Particle class for each body.
 */
class Particle {
 public:
  /**
   * Constructor
   * @param mass mass of the particle
   * @param radius radius of the particle
   */
  Particle(double mass, double radius);

  /**
   * Destructor
   */
  ~Particle();

  double mass;  /**< mass of the particle */
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
  double d(const Particle &particle);
  double v();
  double Ekin();

 private:
  static const int dimen_ = 3;
};

/**
 * @typedef Particles
 * @brief vector of pointers to Particle
 */
typedef std::vector<std::unique_ptr<Particle> > Particles;

void print_particles(const Particles &particles);

#endif  // PARTICLE_H_
    
