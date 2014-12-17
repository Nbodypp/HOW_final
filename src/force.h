/**
 * @file
 * @brief Force class
 */

#ifndef FORCE_H_
#define FORCE_H_
#include "particle.h"

/*extra_force_func is a pointer to a function that takes Particles and 
 *returns pointer to double.  It is the archetype for our extra-Newtonian
 * functions*/
typedef void (*extra_force_func)(Particles,double **); //Previously (double*)[3]

/*Extra_Force_Func_Vec is a std::vector that stores the pointers to all 
 *the extra-Newtonian force functions*/
typedef std::vector<std::unique_ptr<extra_force_func>> Extra_Force_Func_Vec;


class Force {
 public:
  Force();
  ~Force();

  void update_acceleration(const Particles& particles, const Extra_Force_Func_Vec &functions) const;

  void extra_acceleration(const Particles& particles, const Extra_Force_Func_Vec &functions) const;
};


#endif  //FORCE_H_
