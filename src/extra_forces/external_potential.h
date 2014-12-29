/**
 * @file
 *
 * @brief External potential header file
 */

#ifndef EXTERNAL_POTENTIAL_H_
#define EXTERNAL_POTENTIAL_H_

#include "../particle.h"

double calculate_acceleration(Particle particle);

void external_potential(Particles& particles);



#endif  //EXTERNAL_POTENTIAL_H_
