/* A header file a simple force to integrate
 * for the purpose of testing the integrators.
 * It also contains some "global-ish variables"
 * that are useful, for testing purposes, to make
 * accessible to the test*.cc files themselves.
 */

#ifndef SIMPLE_INTEGRATION_H_
#define SIMPLE_INTEGRATION_H_

#include "particle.h"

const double ax_0 = 1.0;
const double ay_0 = 2.0;
const double az_0 = 3.0;

void SimpleIntegration(Particles &particles);

#endif
