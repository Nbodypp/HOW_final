#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <typeinfo>
#include <string.h>
#include "SimpleIni.h"
#include "particle.h"
#include "force.h"
#include "math.h"
#include "integrator.h"
#include "euler.h"
#include "leapfrog.h"

/** Prints this message if the wrong number of command line arguments are given
 */
void intromessage(char *name)
{
  printf("Usage: %s, in_file\n",name);
  printf("      in_file:    Name of the .ini input file with all the input parameters\n");
  exit(0);
}


int main(int argc, char *argv[])
{
  if(argc!=2) //If the wrong number of command line arguments is given
    {
      intromessage(argv[0]);
    }

  // vector of pointers to Particle
  Particles particles;

  CSimpleIniA ini;
  ini.LoadFile(argv[1]);
  double tmpmass, tmpradius;

  // TODO: verify required sections are there
  // TODO: verify required keys are there
  // get settings
  const double dt = atof(ini.GetValue("", "timestep"));
  const double tmax = atof(ini.GetValue("", "tmax"));
  const std::string gravity = ini.GetValue("", "gravity");
  const std::string integrator_name = ini.GetValue("", "integrator");
  printf("#     dt    = %15.8f\n", dt);
  printf("#   tmax    = %15.8e\n", tmax);
  printf("#gravity    = %s\n", gravity.c_str());
  printf("#integrator = %s\n", integrator_name.c_str());

  // Setup particles
  CSimpleIniA::TNamesDepend sections;
  ini.GetAllSections(sections);
  for (auto i = sections.begin(); i != sections.end(); ++i)
  {
    // skip root section -- it's for settings
    if (strcmp(i->pItem, "") == 0) {
      continue;
    }
    std::cout << "#Initializing " << i->pItem << std::endl; 
    tmpmass = atof(ini.GetValue(i->pItem, "mass"));
    tmpradius = atof(ini.GetValue(i->pItem, "radius"));
    particles.push_back(std::unique_ptr<Particle>(new Particle(tmpmass, tmpradius)));
    particles.back()->x = atof(ini.GetValue(i->pItem, "x"));
    particles.back()->y = atof(ini.GetValue(i->pItem, "y"));
    particles.back()->z = atof(ini.GetValue(i->pItem, "z"));
    particles.back()->vx = atof(ini.GetValue(i->pItem, "vx"));
    particles.back()->vy = atof(ini.GetValue(i->pItem, "vy"));
    particles.back()->vz = atof(ini.GetValue(i->pItem, "vz"));
  }
  
  // Setup the force model
  printf("#Setting up a force model\n");
  Force force;

  // Setup the integrator
  printf("#Setting up an integrator\n");
  Integrator *integrator = NULL;
  if (integrator_name.compare("euler") == 0)
  {
    printf("#Setting up an euler integrator\n");
    integrator = new Euler(dt, force);
  }
  else if (integrator_name.compare("leapfrog") == 0)
  {
    printf("#Setting up a leapfrog integrator\n");
    integrator = new Leapfrog(dt, force);
  }
  if (integrator == NULL)
  {
    printf("ERROR: integrator %s is not known\n", integrator_name.c_str()); 
  }

  printf("#Start integration\n");
  double t = 0;
  for (t = 0; t < tmax; t+=dt)
  {
    integrator->step(t, particles);
    print_particles(particles);    // TODO: print to a file
  }

  // Clean up
  delete integrator;
  return 0;

}
