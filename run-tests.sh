#!/usr/bin/env sh

cd src
make nbodypp
make runtest
./runtest
