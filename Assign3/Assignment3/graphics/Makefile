CFLAGS=-Wall
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim_deconstructedO3: galsim_deconstructed.o graphics.o
	gcc -o galsim_deconstructed galsim_deconstructed.o graphics.o -O3 $(LDFLAGS)

galsim_deconstructed.o: galsim_deconstructed.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_deconstructed.c

galsim_git: galsim_git.o graphics.o
	gcc -o galsim_git galsim_git.o graphics.o -O3 $(LDFLAGS)

galsim_git.o: galsim_git.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_git.c

galsim_newO3: galsim_new.o graphics.o
	gcc -o galsim_newO3 galsim_new.o graphics.o -O3 $(LDFLAGS)

galsim_new.o: galsim_new.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim_new.c

galsim_O3: galsim.o graphics.o
	gcc -o galsim_O3 galsim.o graphics.o -O3 $(LDFLAGS)

galsim_test: galsim.o graphics.o
	gcc -o galsim_test galsim.o graphics.o -O3 $(LDFLAGS)

galsim.o: galsim.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c

graphics_test: graphics_test.o graphics.o
	gcc -o graphics_test graphics_test.o graphics.o $(LDFLAGS)

graphics_test.o: graphics_test.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics_test.c

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./graphics_test ./galsim_test ./galsim_O3 ./galsim_new ./galsim_newO3 ./galsim_deconstructedO3 *.o
