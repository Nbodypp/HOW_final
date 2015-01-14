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

runtest: $(addprefix $(testdir)/, test_main.o testParticle.o testForce.o testCollision.o\
	testEuler.o testEuler_SI.o testLeapfrog.o testRK4.o simpleintegration.o)\
	particle.o force_direct.o collision.o euler.o euler_semi_implicit.o leapfrog.o runge-kutta.o
	$(CXX) $(CFLAGS) -o $@ $^

nbodypp: main.o particle.o  force_direct.o euler.o leapfrog.o runge-kutta.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o nbodypp runtest tests/*.o
