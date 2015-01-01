INCDIR=-I../../src
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all: dragforce

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

dragforce: $(addprefix ../../src/, particle.o force_direct.o leapfrog.o) dragforce.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o dragforce
