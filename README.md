Nbodypp
=========

Directory Structure
-------------------
- doc/ documentation
- src/ source code
  * vendor/ third-party libs
    + simpleini/  [INI file parser](https://github.com/brofield/simpleini)
    + catch.hpp   [catch](https://github.com/philsquared/Catch/) testing framework
  * tests/  tests
  * examples/ examples to possibly use for presentation (e.g., earth orbiting sun)
    * png/  where the image files are stored from the examples (not tracked by git)

Documentation
-------------

- You need [doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate
  documentation. In the `src`, do `make doc`, and documentation files will be
  generated in `doc`.
