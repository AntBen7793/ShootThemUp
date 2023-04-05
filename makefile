CC=gcc
CFLAGS=-Wall -std=c17 -pthread
LDFLAGS=-lm -lMLV
OBJ=main.o player.o collision.o enemy.o missile.o level.o missile_enemy.o health_bar.o party.o menu.o
SRC=src/
projet: $(OBJ)
	$(CC) -o projet $(OBJ) $(LDFLAGS) 

main.o: ${SRC}main.c 
	$(CC) -c ${SRC}main.c $(CFLAGS)

player.o: ${SRC}player.c
	$(CC) -c ${SRC}player.c $(CFLAGS)

collision.o: ${SRC}collision.c
	$(CC) -c ${SRC}collision.c $(CFLAGS)

enemy.o: ${SRC}enemy.c
	$(CC) -c ${SRC}enemy.c $(CFLAGS)

missile.o: ${SRC}missile.c
	$(CC) -c ${SRC}missile.c $(CFLAGS)

level.o: ${SRC}level.c
	$(CC) -c ${SRC}level.c $(CFLAGS)

missile_enemy.o: ${SRC}missile_enemy.c
	$(CC) -c ${SRC}missile_enemy.c $(CFLAGS)

health_bar.o: ${SRC}health_bar.c
	$(CC) -c ${SRC}health_bar.c $(CFLAGS)

party.o: ${SRC}party.c
	$(CC) -c ${SRC}party.c $(CFLAGS)

menu.o: ${SRC}menu.c
	$(CC) -c ${SRC}menu.c $(CFLAGS)
	
clean: 
	rm -f *.o
	rm -f *~
	rm -f projet
