#include <iostream>
#include <math.h>
#include "particle.h"
#include "force.h"
#include "runge-kutta.h"
#include "constants.h"
#include "collision.h"

double G = 1;

int main(int argc, char *argv[])
{

  const double mass = 12.; //in solar mass
  const double mass_bh = 1.e7; //in solar mass
  
  Particles p ({
      Particle (mass, 0.001355),  // star1
      Particle (mass, 0.001355),  // star2
      Particle (mass_bh, 0.05843) // blackhole, with Schwarzschild radius
     });

  const double au_to_l_conv = 3.4318965; //Length unit in AU
  const double r = .7/au_to_l_conv;  //separation between the two stars
  const double R_0 = 30./au_to_l_conv; //Initial distance from stars' center of mass to blackhole //orig 100.//30
  const double x_0 = 4.5/au_to_l_conv; //Initial x-coordinate for stars' center of mass //orig 20.//4.5
  
  p[0].x = x_0+r/2.0;
  p[0].y = sqrt(R_0*R_0 - x_0*x_0);
  p[0].vy = -sqrt(G*mass_bh/R_0)- sqrt(G*mass/r)/1.9;

  p[1].x = x_0-r/2.0;
  p[1].y = sqrt(R_0*R_0 - x_0*x_0);
  p[1].vy = -sqrt(G*mass_bh/R_0) + sqrt(G*mass/r)/1.9;

  double dt = 0.000000008; //orig 0.0002
  double t = 0;
  double tmax = .15; //orig .5

  Force force;
  RungeKutta4 integrator (dt, force);
  print_particles(p, std::cout);
  int counter=0;
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    if(counter % 10000 == 0){
      print_particles(p, std::cout);
    }
    if(collision_check_all(p) !=0)
      {
        fprintf(stderr,"#### COLLISION OCCURED!!!!!\n");
        break; //End the integration
      }
    
    counter++;
  }
  return 0;
}
