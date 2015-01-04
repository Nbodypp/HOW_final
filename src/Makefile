# projectdir=$(shell cd ..; pwd)
docdir=../doc
testdir=./tests

INCDIR=-Ivendor -Ivendor/simpleini -I.
LIBDIR=
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR) $(LIBDIR)

.PHONY: clean

all:
	@echo Specify a target

doc: ../doc/Doxyfile
	cd $(docdir) && \
		doxygen Doxyfile

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

runtest: $(addprefix $(testdir)/, test_main.o testParticle.o testForce.o testCollision.o) particle.o force_direct.o collision.o
	$(CXX) $(CFLAGS) -o $@ $^

testEuler_SI: particle.o force_direct.o euler_semi_implicit.o tests/testEuler_SI.o tests/test_main.o
	$(CXX) $(CFLAGS) -o $(testdir)/testEuler_SI $^

nbodypp: main.o particle.o  force_direct.o euler.o leapfrog.o runge-kutta.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o nbodypp runtest tests/*.o
