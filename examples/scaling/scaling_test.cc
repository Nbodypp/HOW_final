#include <iostream>
#include <math.h>
#include <ctime>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"

double G = 1;

int main(int argc, char *argv[])
{
  clock_t start_time, end_time;
  start_time = clock();

  if(argc != 2){
    printf("USAGE: %s number_of_particles\n", argv[0]);
    exit(0);
  }

  const int num = atoi(argv[1]);


  Particles p;

  for(int i=0; i<num; ++i){ //Set up `num` number of particles
    p.push_back(Particle(1.,0.));
    p.back().x = 1. * double(i); //Give each particle a different position and velocity
    p.back().y = 1. * sin(3.14/2.0 * double(i) );
    
    p.back().vz = 0.5 * double(i);
  }


  double dt = 0.0001;
  double t = 0;
  double tmax = 5.;

  Force force;
  Leapfrog integrator (dt, force);

  for (t = 0; t < tmax; t+=dt) {
    integrator.step(t, p);
  }

  end_time = clock();

  double diffms = (end_time - start_time) / (CLOCKS_PER_SEC/1000);
  printf("%d  %e\n",num, diffms);
  
  return 0;
}
