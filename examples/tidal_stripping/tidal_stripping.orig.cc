#include <iostream>
#include <math.h>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"
#include "collision.h"

double G = 1;

int main(int argc, char *argv[])
{

  const double mass = 1.; //in solar mass
  const double mass_bh = 1.e7; //in solar mass
  
  Particles p ({
      Particle (mass, 0.001355),  // star1
      Particle (mass, 0.001355),  // star2
      Particle (mass_bh, 0.05843) // blackhole, with Schwarzschild radius
     });

  const double au_to_l_conv = 3.4318965; //Length unit in AU
  const double r = .3/au_to_l_conv;  //separation between the two stars
  const double R_0 = 100./au_to_l_conv; //Initial distance from stars' center of mass to blackhole //orig 100.
  const double x_0 = 20./au_to_l_conv; //Initial x-coordinate for stars' center of mass //orig 20.
  
  p[0].x = x_0+r/2.0;
  p[0].y = sqrt(R_0*R_0 - x_0*x_0);
  p[0].vy = -sqrt(G*mass_bh/R_0)- sqrt(G*mass/r)/2.0;

  p[1].x = x_0-r/2.0;
  p[1].y = sqrt(R_0*R_0 - x_0*x_0);
  p[1].vy = -sqrt(G*mass_bh/R_0) + sqrt(G*mass/r)/2.0;

  double dt = 0.0002; //orig 0.0002
  double t = 0;
  double tmax = .5; //orig .5

  Force force;
  Leapfrog integrator (dt, force);
  print_particles(p, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    print_particles(p, std::cout);
        if(collision_check_all(p) !=0)
      {
        fprintf(stderr,"#### COLLISION OCCURED!!!!!\n");
        break; //End the integration
      }
  }
  return 0;
}
