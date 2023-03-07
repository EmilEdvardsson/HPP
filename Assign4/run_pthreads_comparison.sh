#!/bin/bash

#remove old output file
rm result.gal

# compile galsim_new
make clean
make galsim_pthreads_graphics

# Run galsim_new
time ./galsim_pthreads_graphics 3000 ~/Github/HPP/Assign4/input_data/ellipse_N_03000.gal 100 0.00001 0 8

# Run compare with output file
./compare 3000 ~/Github/HPP/Assign4/ref_output_data/ellipse_N_03000_after100steps.gal result.gal
