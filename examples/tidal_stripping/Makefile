INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all: tidal_stripping

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

tidal_stripping: $(addprefix ../../src/, particle.o force_direct.o leapfrog.o collision.o) tidal_stripping.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o solarsystem
