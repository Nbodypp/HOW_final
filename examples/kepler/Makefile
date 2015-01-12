INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x -g $(INCDIR)
deps=$(addprefix ../../src/, particle.o force_direct.o\
		   euler.o euler_semi_implicit.o leapfrog.o runge-kutta.o)
.PHONY: all

all: kepler kepler.printtofile kepler.lessprintout

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

kepler: $(deps) kepler.o
	$(CXX) $(CFLAGS) -o $@ $^

kepler.printtofile: $(deps) kepler.printtofile.o
	$(CXX) $(CFLAGS) -o $@ $^

kepler.lessprintout: $(deps) kepler.lessprintout.o
	$(CXX) $(CFLAGS) -o $@ $^

%.energy.dat : kepler
	./kepler $* energy > $*.energy.dat

%.orbit.dat : kepler
	./kepler $* orbit > $*.orbit.dat

testenergy: $(addsuffix .energy.dat, euler eulersi leapfrog rk4)

testorbit: $(addsuffix .orbit.dat, euler eulersi leapfrog rk4)

test: testenergy testorbit
	./makeplots.py *.dat

clean:
	-rm -rf *.o kepler kepler.printtofile kepler.lessprintout
