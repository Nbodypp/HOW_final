Nbodypp
=========

[![Build Status](https://travis-ci.org/Nbodypp/HOW_final.svg?branch=master)](https://travis-ci.org/Nbodypp/HOW_final)

- [ ] more examples - drag force (additional force example), ...
- [ ] output tools
  * write to a binary file
  * for every some time step
- [ ] add and re-arrange tests
- [ ] comparison with analytic solution

## Getting Started

Nbodypp is a C++ library for solving collisional N-body systems. There are two use cases of the code.

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
  Particles p ({
    Particle (1., 0.),        // star
    Particle (0., 0.)  // planet
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

- You may generate the initial condition using a function. `Particles` is
  a typedef of a STL vector of `Particle`s, thus you can use any of its usual
  constructor.

```c++
void init_cond(Particles &particles) {
  // assign initial conditions here
}

int main(int argc, char *argv[])
{
  Particles p (50, Particle(0, 0));  // vector of 50 Particles
  init_cond(p);

  ...
}

```

- You can also add non-gravitational forces by writing functions that changes
  ax, ay, az of particles, and adding them to Force class.

```c++
void dragforce(Particles &particles) {
  for (auto &p : particles) {
    p.ax -= p.vx
    ...
  }
}

int main(int argc, char *argv[])
{
  Particles p (50, Particle(0, 0));  // vector of 50 Particles
  
  Force force;
  Leapfrog integrator (dt, force);
  integrator.add_force(&dragforce);
  ...
}
```

Check out examples/ for more.

For more details, see doxygen documentation.

## Directory Structure

- doc/ documentation
- src/ source code
  * vendor/ third-party libs
    + simpleini/  [INI file parser](https://github.com/brofield/simpleini)
    + catch.hpp   [catch](https://github.com/philsquared/Catch/) testing framework
  * tests/  tests
- examples/

## Documentation

You need [doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate documentation. In the `src`, do `make doc`, and documentation files will be generated in `doc`.

