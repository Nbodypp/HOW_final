#This script is used to run the callgrind profiler on our code.
#The script is specifically designed to test the code in a multiplicity of
# settings and with a multiplicity of integrators
# os/x: use qcachegrind to open profiler output files
# Linux: use kcachegrind to open profiler output files

#make all  #make sure all the executable(s) are current

for integrator in "euler" "eulersi" "leapfrog" "rk4"
do

    valgrind --tool=callgrind --dump-instr=yes --trace-jump=yes --dsymutil=yes --callgrind-out-file="callgrind.out."$integrator".dat" ./kepler $integrator orbit  > temp.$integrator.dat

done
