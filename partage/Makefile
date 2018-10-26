
all: iftest.o
	gcc iftest.c iftun.o -o iftest

iftest.o:
	gcc -c iftun.c

clean:
	rm *.o
	rm iftest
