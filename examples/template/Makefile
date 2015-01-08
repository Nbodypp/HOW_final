#
# This is a boilerplate Makefile for a custom N-body problem.
#

INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)
deps=$(addprefix ../../src/, particle.o force_direct.o leapfrog.o)

.PHONY: all

all: problem

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

problem: $(deps) problem.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o problem
