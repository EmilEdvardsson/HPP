CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim_hybridO3: galsim_hybrid.o graphics.o
	gcc -o galsim_hybrid galsim_hybrid.o graphics.o -O3 $(LDFLAGS)

galsim_hybrid.o: galsim_hybrid.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_hybrid.c

galsim_git: galsim_git.o graphics.o
	gcc -o galsim_git galsim_git.o graphics.o $(LDFLAGS)

galsim_git.o: galsim_git.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_git.c

galsim_newO3: galsim_new.o graphics.o
	gcc -o galsim_newO3 galsim_new.o graphics.o -O3 -funroll-loops $(LDFLAGS)

galsim_new.o: galsim_new.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_new.c -O3

galsim_O3: galsim.o graphics.o
	gcc -o galsim_O3 galsim.o graphics.o -O3 $(LDFLAGS)

galsim_test: galsim.o graphics.o
	gcc -o galsim_test galsim.o graphics.o $(LDFLAGS)

galsim.o: galsim.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c

graphics_test: graphics_test.o graphics.o
	gcc -o graphics_test graphics_test.o graphics.o $(LDFLAGS)

graphics_test.o: graphics_test.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics_test.c

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./graphics_test ./galsim_test ./galsim_O3 ./galsim_new ./galsim_newO3 *.o
