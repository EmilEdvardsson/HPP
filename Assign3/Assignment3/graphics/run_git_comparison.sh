#!/bin/bash

#remove old output file
rm results.gal

# compile galsim_new
make clean
make galsim_git

# Run galsim_new
./galsim_git 100 ~/Github/HPP/Assign3/Assignment3/input_data/ellipse_N_00100.gal 600 0.00001 1

# Run compare with output file
./compare 100 ~/Github/HPP/Assign3/Assignment3/ref_output_data/ellipse_N_00100_after200steps.gal result.gal
