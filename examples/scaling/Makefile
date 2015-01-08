INCDIR=-I../../src -I.
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all: scaling_test

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

scaling_test: $(addprefix ../../src/, particle.o force_direct.o leapfrog.o) scaling_test.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o scaling_test
