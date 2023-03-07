pi: pi.c
	gcc -Wall -O3 -o pi pi.c

pipthreads: pipthreads.c
	gcc -Wall -O3 -o pipthreads pipthreads.c -pthread

piopenmp: piopenmp.c
	gcc -Wall -O3 -o piopenmp piopenmp.c -fopenmp

clean:
	rm -f pi pipthreads piopenmp
