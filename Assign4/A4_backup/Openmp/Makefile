CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim_omp: galsim_omp.o graphics.o
	gcc -o galsim_omp galsim_omp.o graphics.o -O3 -fopenmp $(LDFLAGS)

galsim_omp.o: galsim_omp.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_omp.c -fopenmp

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./galsim ./galsim_graphics ./galsim_omp ./galsim_pthreads_graphics ./galsim_omp_graphics ./galsim_graphics *.o
