CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim:
	gcc -o galsim galsim.c -O3 $(LDFLAGS)

clean:
	rm -f ./galsim *.o
