CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim_pthreads: galsim_pthreads.o
	gcc -o galsim_pthreads galsim_pthreads.o -O3 -pthread $(LDFLAGS)

galsim_pthreads.o: galsim_pthreads.c
	gcc $(CFLAGS) $(INCLUDES) -c galsim_pthreads.c -pthread

clean:
	rm -f ./galsim ./galsim_graphics ./galsim_omp ./galsim_pthreads_graphics ./galsim_omp_graphics ./galsim_graphics *.o
