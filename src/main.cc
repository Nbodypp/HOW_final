#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "SimpleIni.h"
#include "particle.h"

void delete_particle(Particle* const ptr)
{
  delete ptr;
}

int main(int argc, char *argv[])
{

  // vector of pointers to Particle
  std::vector<Particle *> particles;

  CSimpleIniA ini;
  ini.LoadFile("test.ini");
  double tmpmass, tmpradius;

  // TODO: verify required sections are there
  // TODO: verify required keys are there
  // get all sections
  CSimpleIniA::TNamesDepend sections;
  CSimpleIniA::TNamesDepend::const_iterator i;
  ini.GetAllSections(sections);
  for (i = sections.begin(); i != sections.end(); ++i)
  {
    if (strcmp(i->pItem, "settings") == 0)
    {
      const double dt = atof(ini.GetValue("settings", "timestep"));
      const double tmax = atof(ini.GetValue("settings", "tmax"));
      const char * gravity = ini.GetValue("settings", "gravity");
      continue;
    }
    std::cout << i->pItem << std::endl; 
    tmpmass = atof(ini.GetValue(i->pItem, "mass"));
    tmpradius = atof(ini.GetValue(i->pItem, "radius"));
    particles.push_back(new Particle(tmpmass, tmpradius));
  }

  printf("     dt = %15.8f\n", dt);
  printf("   tmax = %15.8e\n", tmax);
  printf("gravity = %15s\n", gravity);
  
  Nparticles = particles.size();
  printf("number of particles = %d\n", Nparticles);
  for (int i = 0; i < Nparticles; ++i)
  {
    particles[i]->print();
  }

  // free all memory
  std::for_each(particles.begin(), particles.end(), delete_particle);
  return 0;

}
