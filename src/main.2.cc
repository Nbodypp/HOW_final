#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <string>
#include "math.h"

#include "SimpleIni.h"

#include "particle.h"
#include "force.h"
#include "integrator.h"
#include "euler.h"
#include "leapfrog.h"
#include "runge-kutta.h"
#include "constants.h"
#include "extra_forces/external_potential.h"

double G;

// check if input file is valid
void check_inputfile(CSimpleIniA &ini) {
  const char *tmp;

  // keys to check in the root section
  std::string keys[4] = {
    "timestep", "tmax", "gravity", "integrator"};
  for (int i = 0; i < 4; ++i) {
    tmp = ini.GetValue("", keys[i].c_str());
    if (tmp == NULL) {
      throw std::runtime_error(keys[i] + " does not exist");
    }
  }

  int np = 0;  // number of particles
  // keys to check for every particle (section)
  std::string pkeys[8] = {
    "mass", "radius", "x", "y", "z", "vx", "vy", "vz"};
  CSimpleIniA::TNamesDepend sections;
  ini.GetAllSections(sections);
  for (auto i = sections.begin(); i != sections.end(); ++i)
  {
    // skip root section -- it's for settings
    if (strcmp(i->pItem, "") == 0) {
      continue;
    }
    np++;
    for (int j = 0; j < 8; ++j) {
      tmp = ini.GetValue(i->pItem, pkeys[j].c_str());
      try {
        std::stod(tmp);
      } catch(const std::exception &e) {
        char buf[100];
        sprintf(buf, "%s:%s %s", i->pItem, pkeys[j].c_str(), e.what());
        throw std::runtime_error(buf);
      }
    }
  }
  if (np <= 1) {
    throw std::runtime_error("less than 2 particles found");
  }
}

int main(int argc, char *argv[])
{
  // verify input file
  if (argc != 2) {
    printf("USAGE: %s <inputfile>\n", argv[0]);
    exit(1);
  }
  CSimpleIniA ini;
  ini.LoadFile(argv[1]);
  try {
    check_inputfile(ini);
  } catch(const std::exception &e) {
    std::cerr << "ERROR: invalid input - " << e.what() << std::endl;
    exit(1);
  }

  double tmpmass, tmpradius;
  Particles particles;  //vector of pointers to Particle class instances

  // get settings
  const double dt = atof(ini.GetValue("", "timestep"));
  const double tmax = atof(ini.GetValue("", "tmax"));
  const std::string gravity = ini.GetValue("", "gravity");
  const std::string integrator_name = ini.GetValue("", "integrator");
  G = atof(ini.GetValue("", "G", "1.0"));
  fprintf(stderr, "#         G = %15.8e\n", G);
  fprintf(stderr, "#        dt = %15.8f\n", dt);
  fprintf(stderr, "#      tmax = %15.8e\n", tmax);
  fprintf(stderr, "#   gravity = %s\n", gravity.c_str());
  fprintf(stderr, "#integrator = %s\n", integrator_name.c_str());

  // Setup particles
  CSimpleIniA::TNamesDepend sections;
  ini.GetAllSections(sections);
  for (auto i = sections.begin(); i != sections.end(); ++i)
  {
    // skip root section -- it's for settings
    if (strcmp(i->pItem, "") == 0) {
      continue;
    }
    std::cerr << "#Initializing " << i->pItem << std::endl; 
    tmpmass = atof(ini.GetValue(i->pItem, "mass"));
    tmpradius = atof(ini.GetValue(i->pItem, "radius"));
    particles.push_back(Particle(tmpmass, tmpradius));
    particles.back().x = atof(ini.GetValue(i->pItem, "x"));
    particles.back().y = atof(ini.GetValue(i->pItem, "y"));
    particles.back().z = atof(ini.GetValue(i->pItem, "z"));
    particles.back().vx = atof(ini.GetValue(i->pItem, "vx"));
    particles.back().vy = atof(ini.GetValue(i->pItem, "vy"));
    particles.back().vz = atof(ini.GetValue(i->pItem, "vz"));
  }
  
  // Setup the force model
  std::cerr << "#Setting up a force model" << std::endl;
  Force force;

  // Setup extra force(s)
  force.add_force(&external_potential)

  // Setup the integrator
  std::cerr << "#Setting up an integrator" << std::endl;
  Integrator *integrator = NULL;
  if (integrator_name.compare("euler") == 0)
  {
    std::cerr << "#Setting up an euler integrator" << std::endl;
    integrator = new Euler(dt, force);
  }
  else if (integrator_name.compare("leapfrog") == 0)
  {
    std::cerr << "#Setting up a leapfrog integrator" << std::endl;
    integrator = new Leapfrog(dt, force);
  }
  else if (integrator_name.compare("rk4") == 0) {
    std::cerr << "#Setting up a runge-kutta integrator" << std::endl;
    integrator = new RungeKutta4(dt, force);
  }
  if (integrator == NULL)
  {
    fprintf(stderr, "ERROR: integrator %s is not known\n",
            integrator_name.c_str()); 
  }

  std::cerr << "#Starting integration" << std::endl;
  double t = 0;
  print_particles(particles, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator->step(t, particles);
    print_particles(particles, std::cout);    // TODO: print to a file
  }

  // Clean up
  delete integrator;
  return 0;

}
