/**
 * \file
 *
 * \brief Particle class
 *
 * Longer description goes here
 */
#ifndef PARTICLE_H_
#define PARTICLE_H_

/**
 * \brief Particle class for each body
 */
class Particle {
 public:
  Particle(double mass, double radius, int dimen);
  ~Particle();
  double r[dimen];
  double v[dimen];

 private:
  const double mass_;
  const double radius_;
  const int    dimen_;
};

#endif  // PARTICLE_H_
    
