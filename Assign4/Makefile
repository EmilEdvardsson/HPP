CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim_graphics: galsim_graphics.o graphics.o
	gcc -o galsim_graphics galsim_graphics.o graphics.o -O3 $(LDFLAGS)

galsim: galsim.o
	gcc -o galsim galsim.o -O3 $(LDFLAGS)

galsim_omp_graphics: galsim_omp_graphics.o graphics.o
	gcc -o galsim_omp_graphics galsim_omp_graphics.o graphics.o -O3 -fopenmp -ffast-math $(LDFLAGS)

galsim_pthreads_graphics: galsim_pthreads_graphics.o graphics.o
	gcc -o galsim_pthreads_graphics galsim_pthreads_graphics.o graphics.o -O3 -pthread -ffast-math $(LDFLAGS)

galsim_omp: galsim_omp.o
	gcc -o galsim_omp galsim_omp.o -O3 -fopenmp $(LDFLAGS)

galsim_graphics.o: galsim_graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_graphics.c

galsim_omp_graphics.o: galsim_omp_graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_omp_graphics.c -fopenmp

galsim_pthreads_graphics.o: galsim_pthreads_graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_pthreads_graphics.c -pthread

galsim_omp.o: galsim_omp.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_omp.c

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./galsim ./galsim_graphics ./galsim_omp ./galsim_pthreads_graphics ./galsim_omp_graphics ./galsim_graphics *.o
