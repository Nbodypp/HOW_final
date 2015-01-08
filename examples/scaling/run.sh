#!/bin/bash

echo "#Format: number_of_particles run_time_in_ms"
for num in 1 2 4 8 16 24 32 40 48 56 64 72 80
do
    ./scaling_test $num

done
