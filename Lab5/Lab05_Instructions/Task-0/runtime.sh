#!/bin/bash
echo "Regularcode:"
time ./regularcode
echo "Regularcode-O2:"
time ./regularcode-O2
echo "Regularcode-O3:"
time ./regularcode-O3
echo "Mallocycode:"
time ./mallocycode
echo "Mallocycode-O2:"
time ./mallocycode-O2
echo "Mallocycode-O3:"
time ./mallocycode-O3
echo "Sleepycode:"
time ./sleepycode
echo "Sleepycode-O2:"
time ./sleepycode-O2
echo "Sleepycode-O3:"
time ./sleepycode-O3
echo "Threadedcode:"
time ./threadedcode
echo "Threadedcode-O2:"
time ./threadedcode-O2
echo "Threadedcode-O3:"
time ./threadedcode-O3


time ./sleepycode
