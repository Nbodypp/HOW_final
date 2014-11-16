#ifndef PARTICLE_H_
#define PARTICLE_H_


class Particle {
 public:
  Particle(double mass, double radius, int dimen);
  ~Particle();
  double r[dimen];
  double v[dimen];

 private:
  const double mass_; //defined this way, the mass and radius can't change, so cataclysmic collisions aren't possible as the code is written.
  const double radius_;
  const int    dimen_;
};

#endif  // PARTICLE_H_
    
