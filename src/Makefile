projectdir=$(shell cd ..; pwd)
docdir=$(projectdir)/doc
srcdir=$(projectdir)/src
testdir=$(srcdir)/tests

INCDIR=-Ivendor -Ivendor/simpleini -I$(srcdir)
LIBDIR=
CFLAGS=-Wall -std=c++0x $(INCDIR) $(LIBDIR)

.PHONY: clean

all:
	@echo Specify a target

doc: ../doc/Doxyfile
	cd $(docdir) && \
		doxygen Doxyfile

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

testParticle: particle.o tests/testParticle.o
	$(CXX) $(CFLAGS) -o $(testdir)/testParticle $^

nbodypp: main.o particle.o  force_direct.o euler.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o nbodypp
