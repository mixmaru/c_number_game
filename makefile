# Makefile
a.out: game.o
	gcc -Wall -O2 -o a.out game.o
game.o: game.c
	gcc -c game.c
clean:
	rm -f *.o a.out
