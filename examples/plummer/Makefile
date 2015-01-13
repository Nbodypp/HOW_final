INCDIR=-I../../src
CXXFLAGS=-Wall -O3 -std=c++0x $(INCDIR)

.PHONY: all

all: plummer

plummer: $(addprefix ../../src/, particle.o force_direct.o leapfrog.o) plummer.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	-rm -rf *.o plummer
