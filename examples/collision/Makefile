INCDIR=-I../../src -I../../src/vendor -I../../src/vendor/simpleini
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all:collision

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

collision: $(addprefix ../../src/, particle.o force_direct.o euler.o leapfrog.o runge-kutta.o collision.o) collision.main.o
	$(CXX) $(CFLAGS) -o $@ $^
clean:
	-rm -rf *.o collision
