Nbodypp
=========

[![Build Status](https://travis-ci.org/Nbodypp/HOW_final.svg?branch=master)](https://travis-ci.org/Nbodypp/HOW_final)

Nbodypp is a C++ toolkit for solving collisional N-body dynamics. Please read
through this document to use this code.

## Directory Structure

- doc/ documentation
- src/ source code
  * vendor/ third-party libs
    + simpleini/  [INI file parser](https://github.com/brofield/simpleini)
    + catch.hpp   [catch](https://github.com/philsquared/Catch/) testing framework
  * tests/  tests
- examples/
  * solarsystem : inner planets of the Solar system. Both input file and the
    problem source code is included.
  * dragforce : external velocity-dependent drag force slows down the particle
  * earthmoon : Sun's gravity is added in as an external force
  * plummer : self-gravity of a plummer sphere

## Install

Requirements: Nbody++ requires C++11 compiler such as clang version>=3.3 or gcc version>=4.6. To use python scripts in `scripts/`, you need [numpy](numpy.org) and [matplotlib](matplotlib.org) installed. For `vis.py` which renders OpenGL visualization, you need the development version of [vispy](https://github.com/vispy/vispy).

To obtain a copy of the code, clone this repository.
```
git clone https://github.com/Nbodypp/HOW_final
```
To build, change directory to `src/` and type `make`. This will compile nbodypp executable, and the doxygen documentation in `doc/`.

## Getting Started

There are two use cases of the code.

### Using nbodypp
If you simply want to solve for the orbits of N-body system under mutual gravity, you can write a configuration file in INI format. Settings are in root section, and each [section] defines the mass and the initial condition (x, y, z, vx, vy, vz) of a particle. You may choose an arbitrary mass, length, and time units by specifying the gravitational constant G. This is an example input file for the circular motion of a test particle (`mass = 0`).

Radius is not yet implemented.

```ini
; Nbodypp test input configuration file
G = 1.                  ;gravitational constant
timestep = 0.01
tmax = 1
gravity = direct
integrator = euler
output = result.dat

[star]
mass = 1
radius = 1
x = 0
y = 0
z = 0
vx = 0
vy = 0
vz = 0

[planet]
mass = 0.
radius =  0.01
x = 1
y = 0
z = 0
vx = 0
vy = 1
vz = 0
```

To run, do `./nbodypp test.ini` and the orbits of each particle will be printed
to stdout in the format [x, y, z, vx, vy, vz] * Nparticles for each time step
in a line. 

### Defining your own problem

You can also define your own problem using the library in C++. The same problem above can be solved with the following code.

```c++
#include <iostream>
#include "particle.h"
#include "force.h"
#include "leapfrog.h"
#include "constants.h"

double G = 1;    // G must be global

int main(int argc, char *argv[])
{
  // Particles is an STL vector of `Particle`s
  Particles p ({
    Particle (1., 0.),        // star
    Particle (0., 0.)         // planet
    });
  
  // All particles are initialized with x, y, z, vx, vy, vz = 0
  p[1].x = 1.;
  p[1].vy = 1.;

  double dt = 0.01;
  double t = 0;
  double tmax = 1.;

  Force force;
  Leapfrog integrator (dt, force);
  print_particles(p, std::cout);
  for (t = 0; t < tmax; t+=dt)
  {
    integrator.step(t, p);
    print_particles(p, std::cout);
  }
  return 0;
}
```

You need a Makefile to make the problem.

```makefile
INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all clean

all: circular

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

circular : $(addprefix ../../src/, particle.o force_direct.o leapfrog.o) circular.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o circular
```
- You can also add non-gravitational forces by writing functions that changes
  ax, ay, az of particles, and adding them to Force class. These functions should take `Particles&` and return void. For example, to add a drag force in the opposite direction of particles' velocity,

```c++
void dragforce(Particles &particles) {
  for (auto &p : particles) {
    p.ax -= p.vx
    p.ay -= p.vy
    p.az -= p.vz
  }
}

int main(int argc, char *argv[])
{
  Particles p (50, Particle(0, 0));  // vector of 50 Particles
  
  Force force;
  force.add_force(&dragforce);
  Leapfrog integrator (dt, force);
  ...
}
```

Copy and modify the examples/template` which contains boilerplate problem and makefile to write your own.

Also check out examples/ for more.

## Examples

- solarsystem : inner planets of the Solar system
- resoscatter : binary-single interaction
- dragforce : 
- earthmoon : Earth and Moon moving in a Sun-like gravitational potential.  Example and proof of concept of defining an external central potential. 'plot.py' will take the output from 'earthmoon' and plot the orbits of the Earth and Moon


TODO: complete example description

## Documentation

For more details of each classes and functions, see doxygen documentation.
You need [doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate documentation. In the `src`, do `make doc`, and documentation files will be generated in `doc`.
