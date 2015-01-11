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

clean:
	-rm -rf *.o resoscatter *.dat
