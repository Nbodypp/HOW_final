#ifndef ORBITOBJECT_H_
#define ORBITOBJECT_H_


class Orbit_Object {
 public:
  Orbit_Object(double mass, double radius, int dimen);
  ~Orbit_Object();
  double r[dimen];
  double v[dimen];

 private:
  const double mass_; //defined this way, the mass and radius can't change, so cataclysmic collisions aren't possible as the code is written.
  const double radius_;
  const int    dimen_;
};

#endif  // ORBITOBJECT_H_
    
