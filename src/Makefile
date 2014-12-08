projectdir=$(shell cd ..; pwd)
docdir=$(projectdir)/doc
srcdir=$(projectdir)/src

INCDIR=-Ivendor -Ivendor/simpleini
LIBDIR=
CFLAGS=-Wall -std=c++0x $(INCDIR) $(LIBDIR)

.PHONY: clean

doc: ../doc/Doxyfile
	cd $(docdir) && \
		doxygen Doxyfile

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

testParticle: particle.o testParticle.o
	$(CXX) $(CFLAGS) -o testParticle particle.o testParticle.o

nbodypp: main.o particle.o  force_direct.o euler.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o nbodypp
