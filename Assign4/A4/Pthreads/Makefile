CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim: galsim.o
	gcc -o galsim galsim.o -O3 -pthread $(LDFLAGS)

galsim.o: galsim.c
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c -pthread

clean:
	rm -f ./galsim *.o
