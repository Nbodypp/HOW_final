/**   \brief The acceleration class file

      This file defines the meat of the acceleration class, which can calculate the acceleration for the particles.
 */

#include <math.h>
#include "acceleration.h"
#include "constants.h"


Acceleration::Acceleration(double mass2, double *r, int dimen, double *a) /** Constructor for Acceleration class*/
  : mass2_(mass2),
    r_(r),
    dimen_(dimen),
    a_(a)
{}

Acceleration::~Acceleration() /** Destructor for Acceleration class*/
{}



/** \brief Function to calculate acceleration between two particles

    This function calculates the acceleration between two particles using Newton's law of gravity
*/
int Acceleration::calculate_acceleration(const double mass2, const double *r, const int dimen, double *a) const
{
  int i; /** index, nothing special*/
  double r_mag; /** Calculate the magntiude of the vector r between two particles*/

  //Calculate r_mag
  r_mag=0.;
  for(i=0; i<dimen; i++)
    {
      r_mag += r[i] * r[i];
    }
  r_mag=sqrt(r_mag);

  
  for(i=0; i<dimen; i++)
    {
      a[i] = G_ * mass2 * r[i] / pow(r_mag,3);
    }

  return 0;
}


//Joshua's questions: how to handle G?  Do we only need it in this class, as so it should only be defined in this class?  We can define it with a header file I suppose.  I will do that.
//Do we want to calculate the force or the acceleration between two particles?  The force will be the same but the acceleration won't be; thus if we calculate force we can apply it to both particles (if we figure out how to do that)
