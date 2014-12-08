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
#include "euler.h"

int main(int argc, char *argv[])
{
  // vector of pointers to Particle
  Particles particles;

  CSimpleIniA ini;
  ini.LoadFile("test.ini");
  double tmpmass, tmpradius;

  // TODO: verify required sections are there
  // TODO: verify required keys are there
  // get settings
  const double dt = atof(ini.GetValue("", "timestep"));
  const double tmax = atof(ini.GetValue("", "tmax"));
  const std::string gravity = ini.GetValue("", "gravity");
  printf("#     dt = %15.8f\n", dt);
  printf("#   tmax = %15.8e\n", tmax);
  printf("#gravity = %s\n", gravity.c_str());

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
  
  double t = 0;
  Euler integrator (dt, particles.size());  
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, particles);
    print_particles(particles);
  }

  return 0;

}
