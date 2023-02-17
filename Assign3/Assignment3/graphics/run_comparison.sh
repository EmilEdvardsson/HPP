#!/bin/bash

#remove old output file
rm output.gal

# compile galsim_new
make clean
make galsim_newO3

# Run galsim_new
time ./galsim_newO3 3000 ~/Github/HPP/Assign3/Assignment3/input_data/ellipse_N_03000.gal 100 0.00001 0

# Run compare with output file
#./compare 3000 ~/Github/HPP/Assign3/Assignment3/ref_output_data/ellipse_N_03000_after200steps.gal output.gal
