#!/bin/bash

#remove old output file
rm output.gal

# compile galsim_new
make clean
make galsim_new

# Run galsim_new
./galsim_new 1000 ~/Github/HPP/Assign3/Assignment3/input_data/ellipse_N_01000.gal 200 0.00001 0

# Run compare with output file
./compare 1000 ~/Github/HPP/Assign3/Assignment3/ref_output_data/ellipse_N_01000_after200steps.gal output.gal
