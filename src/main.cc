#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "SimpleIni.h"
#include "particle.h"


typedef std::vector<std::unique_ptr<Particle>> Particles;

void print_particles(Particles &particles) {
  std::cout << particles.size() << std::endl;
}

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
  const double dt = atof(ini.GetValue("settings", "timestep"));
  const double tmax = atof(ini.GetValue("settings", "tmax"));
  const std::string gravity = ini.GetValue("settings", "gravity");
  // get all sections
  CSimpleIniA::TNamesDepend sections;
  CSimpleIniA::TNamesDepend::const_iterator i;
  ini.GetAllSections(sections);
  for (i = sections.begin(); i != sections.end(); ++i)
  {
    if (strcmp(i->pItem, "settings") == 0) {
      continue;
    }
    std::cout << i->pItem << std::endl; 
    tmpmass = atof(ini.GetValue(i->pItem, "mass"));
    tmpradius = atof(ini.GetValue(i->pItem, "radius"));
    particles.push_back(std::unique_ptr<Particle>(new Particle(tmpmass, tmpradius)));
  }

  printf("     dt = %15.8f\n", dt);
  printf("   tmax = %15.8e\n", tmax);
  std::cout << "gravity = " << gravity << std::endl;
  
  const int Nparticles = particles.size();
  printf("number of particles = %d\n", Nparticles);
  print_particles(particles);
  for (int i = 0; i < Nparticles; ++i)
  {
    particles[i]->print();
  }

  // free all memory
  // std::for_each(particles.begin(), particles.end(), delete_particle);
  return 0;

}
