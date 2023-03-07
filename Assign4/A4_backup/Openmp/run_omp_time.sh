#!/bin/bash


# compile galsim_new
make clean
make galsim_omp

# Run galsim_new
./galsim_omp 10000 ~/Github/HPP/Assign4/input_data/ellipse_N_10000.gal 1000 0.0001 1 32

