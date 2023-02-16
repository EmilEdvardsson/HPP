#!/bin/bash

#remove old output file
rm output.gal

# compile galsim_new
make clean
make galsim_hybrid

# Run galsim_new
./galsim_hybrid 100 ~/Github/HPP/Assign3/Assignment3/input_data/ellipse_N_00100.gal 200 0.00001 1

# Run compare with output file
./compare 100 ~/Github/HPP/Assign3/Assignment3/ref_output_data/ellipse_N_00100_after200steps.gal output.gal
