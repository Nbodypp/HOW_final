INCDIR=-I../../src -I../../src/vendor -I../../src/vendor/simpleini
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all:earthmoon

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

earthmoon: $(addprefix ../../src/, particle.o force_direct.o euler.o leapfrog.o runge-kutta.o) earthmoon.main.o external_central_potential.o
	$(CXX) $(CFLAGS) -o $@ $^
clean:
	-rm -rf *.o earthmoon
