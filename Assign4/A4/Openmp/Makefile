CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim: galsim.o
	gcc -o galsim galsim.o -O3 -fopenmp $(LDFLAGS)

galsim.o: galsim.c
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c -fopenmp

clean:
	rm -f ./galsim *.o
