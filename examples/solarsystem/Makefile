INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all: solarsystem

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

solarsystem: $(addprefix ../../src/, particle.o force_direct.o leapfrog.o) solarsystem.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o solarsystem
