#!/bin/bash

n=20


echo "#Format: number_of_particles run_time_in_ms"
for num_part in 1 2 4 8 16 24 32 40 48 56 64 72 80
do
    echo "   "$num_part >&2
    for ((j=0;j<$n;j++))
    do
        echo $j >&2
        ./scaling_test $num_part
    done
done
