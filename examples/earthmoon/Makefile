INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)
deps=$(addprefix ../../src/, particle.o force_direct.o leapfrog.o)

.PHONY: all

all: earthmoon

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

earthmoon: $(deps) earthmoon.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o earthmoon
