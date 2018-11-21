
all: iftun.o
	gcc iftest.c iftun.o -o iftest

tun0: extremite.o iftun.o splitter.c
	gcc extremite.o iftun.o splitter.c -o splitter

ext: extremite.o iftun.o clientExtremiteIn.c clientExtremiteOut.c
	gcc extremite.o iftun.o clientExtremiteIn.c -o extIn
	gcc extremite.o iftun.o clientExtremiteOut.c -o extOut

iftun.o: iftun.c
	gcc -c iftun.c

extremite.o: extremite.c iftun.o
	gcc  iftun.o extremite.c -c

clean:
	rm *.o
	rm iftest
