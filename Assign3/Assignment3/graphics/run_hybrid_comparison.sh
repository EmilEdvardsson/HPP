#!/bin/bash

#remove old output file
rm output.gal

# compile galsim_new
make clean
make galsim_deconstructedO3

# Run galsim_new
time ./galsim_deconstructed 2000 ~/Github/HPP/Assign3/Assignment3/input_data/ellipse_N_02000.gal 200 0.00001 0

# Run compare with output file
./compare 2000 ~/Github/HPP/Assign3/Assignment3/ref_output_data/ellipse_N_02000_after200steps.gal output.gal
