/**   \brief The acceleration header file

      This file is the header file for the acceleration function, which can calculate the acceleration for the particles.
 */

#ifndef ACCELERATION_H_
#define ACCELERATION_H_

class Acceleration {

 public:
  Acceleration(double mass2, double *r, int dimen, double *a);
  ~Acceleration();
  int calculate_acceleration(const double mass2, const double *r, const int dimen, double *a) const; /** calculates acceleration */

 private:
  //const double mass1_; /** Mass of particle 1, current particle under consideration */
  const double mass2_; /** Mass of particle 2, the particle providing the force acting on current particle under consideration */
  const double *r_; /** Pointer to the radius between the two particles */
  const int dimen_; /** The number of dimensions for r */
  double *a_; /** Pointer to the array storing the acceleration*/

};


#endif  // ACCELERATION_H_
