CC=gcc
CFLAGS=-Wall -std=c17 -pthread
LDFLAGS=-lm -lMLV
OBJ=main.o player.o collision.o enemy.o missile.o
SRC=src/
projet: $(OBJ)
	$(CC) -o projet $(OBJ) $(LDFLAGS) 

main.o: ${SRC}main.c ${SRC}player.c ${SRC}collision.c ${SRC}enemy.c ${SRC}missile.c 
	$(CC) -c ${SRC}main.c $(CFLAGS)

player.o: ${SRC}player.c
	$(CC) -c ${SRC}player.c $(CFLAGS)

collision.o: ${SRC}collision.c
	$(CC) -c ${SRC}collision.c $(CFLAGS)

enemy.o: ${SRC}enemy.c
	$(CC) -c ${SRC}enemy.c $(CFLAGS)

missile.o: ${SRC}missile.c
	$(CC) -c ${SRC}missile.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~
	rm -f projet
