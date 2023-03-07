CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror -fopenmp
LDFLAGS = -fopenmp
RM = /bin/rm -f
OBJS = main.o sort_funcs_old.o
EXECUTABLE = sort_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

sort_funcs.o: sort_funcs.h sort_funcs_old.c
	$(CC) $(CFLAGS) -c sort_funcs_old.c

main.o: main.c sort_funcs.h
	$(CC) $(CFLAGS) -c main.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
