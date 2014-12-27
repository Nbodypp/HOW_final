Nbodypp
=========

[![Build Status](https://travis-ci.org/Nbodypp/HOW_final.svg?branch=master)](https://travis-ci.org/Nbodypp/HOW_final)

- [ ] more examples - drag force (additional force example), ...
- [ ] output tools
  * write to a binary file
  * for every some time step
- [ ] add and re-arrange tests
- [ ] comparison with analytic solution

Directory Structure
-------------------
- doc/ documentation
- src/ source code
  * vendor/ third-party libs
    + simpleini/  [INI file parser](https://github.com/brofield/simpleini)
    + catch.hpp   [catch](https://github.com/philsquared/Catch/) testing framework
  * tests/  tests
- examples/

Documentation
-------------

- You need [doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate
  documentation. In the `src`, do `make doc`, and documentation files will be
  generated in `doc`.
