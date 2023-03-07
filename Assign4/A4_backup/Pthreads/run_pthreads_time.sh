#!/bin/bash


# compile galsim_new
make clean
make galsim_pthreads

# Run galsim_new
time ./galsim_pthreads 3000 ~/Github/HPP/Assign4/input_data/ellipse_N_03000.gal 100 0.00001 0 32

