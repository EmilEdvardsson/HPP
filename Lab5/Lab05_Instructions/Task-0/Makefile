all: regularcode regularcode-O2 regularcode-O3 mallocycode mallocycode-O2 mallocycode-O3 sleepycode sleepycode-O2 sleepycode-O3 threadedcode threadedcode-O2 threadedcode-O3

regularcode: regularcode.c
	gcc regularcode.c -o regularcode
regularcode-O2: regularcode.c
	gcc regularcode.c -o regularcode-O2 -O2
regularcode-O3: regularcode.c
	gcc regularcode.c -o regularcode-O3 -O3
mallocycode: mallocycode.c
	gcc mallocycode.c -o mallocycode
mallocycode-O2: mallocycode.c
	gcc mallocycode.c -o mallocycode-O2 -O2
mallocycode-O3: mallocycode.c
	gcc mallocycode.c -o mallocycode-O3 -O3
sleepycode: sleepycode.c
	gcc sleepycode.c -o sleepycode
sleepycode-O2: sleepycode.c
	gcc sleepycode.c -o sleepycode-O2 -O2
sleepycode-O3: sleepycode.c
	gcc sleepycode.c -o sleepycode-O3 -O3
threadedcode: threadedcode.c
	gcc -lpthread threadedcode.c -o threadedcode
threadedcode-O2: threadedcode.c
	gcc -lpthread threadedcode.c -o threadedcode-O2 -O2
threadedcode-O3: threadedcode.c
	gcc - lpthread threadedcode.c -o threadedcode-O3 -O3
clean:
	rm -f regularcode regularcode-O2 regularcode-O3 mallocycode mallocycode-O2 mallocycode-O3 sleepycode sleepycode-O2 sleepycode-O3 threadedcode threadedcode-O2 threadedcode-O3
