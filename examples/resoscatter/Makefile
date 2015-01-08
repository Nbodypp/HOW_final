INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)
deps=$(addprefix ../../src/, particle.o force_direct.o\
		   euler.o euler_semi_implicit.o leapfrog.o runge-kutta.o)
.PHONY: all

all: resoscatter

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

resoscatter: $(deps) resoscatter.o
	$(CXX) $(CFLAGS) -o $@ $^

%.energy.dat : resoscatter
	./resoscatter $* energy > $*.energy.dat

%.orbit.dat : kepler
	./kepler $* orbit > $*.orbit.dat

testenergy: $(addsuffix .energy.dat, euler eulersi leapfrog rk4)

testorbit: $(addsuffix .orbit.dat, euler eulersi leapfrog rk4)

test: testenergy testorbit
	./makeplots.py *.dat

clean:
	-rm -rf *.o resoscatter *.dat
