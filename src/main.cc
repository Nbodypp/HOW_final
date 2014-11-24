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
  std::cout << "number of particles = "<< particles.size() << std::endl;
  for (auto i = particles.begin(); i < particles.end(); ++i) {
    (*i)->print();
  }
}

void update_accerelation(Particles &particles)
{
  for (int i = 0; i < particles.size(); ++i)
  {
    double ax = 0;
    for (int j = 0; j < particles.size(); ++j)
    {
      if (j==i)
      {
        continue;
      }
      ax += particles[j]->mass / ((*particles[i])-(*particles[j]));
    }
    particles[i]->ax = ax;
  }

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
    std::cout << "Initializeing " << i->pItem << std::endl; 
    tmpmass = atof(ini.GetValue(i->pItem, "mass"));
    tmpradius = atof(ini.GetValue(i->pItem, "radius"));
    particles.push_back(std::unique_ptr<Particle>(new Particle(tmpmass, tmpradius)));
    particles.back()->x = atof(ini.GetValue(i->pItem, "x"));
    particles.back()->y = atof(ini.GetValue(i->pItem, "y"));
    particles.back()->z = atof(ini.GetValue(i->pItem, "z"));
  }

  
  print_particles(particles);
  update_accerelation(particles);
  print_particles(particles);

  return 0;

}
