CC=gcc
WIN=x86_64-w64-mingw32-gcc
CFLAGS=-Wall -std=c17 -pthread #-I/usr/include/MLV -L/usr/lib # Ajouter l'option d'inclusion ici
LDFLAGS=-lm -lMLV  # Ajouter l'option de bibliothèque ici
OBJ=main.o player.o collision.o enemy.o missile.o level.o missile_enemy.o health_bar.o party.o menu.o bonus.o nuke.o keyboard.o end.o
SRC=src/

projet: $(OBJ)
	$(CC) -o projet $(OBJ) $(LDFLAGS) 
#	$(WIN) -o projet.exe $(OBJ) $(LDFLAGS) 

main.o: ${SRC}main.c 
	$(CC) -c ${SRC}main.c $(CFLAGS)
#	$(WIN) -c ${SRC}main.c $(CFLAGS)

player.o: ${SRC}player.c
	$(CC) -c ${SRC}player.c $(CFLAGS)
#	$(WIN) -c ${SRC}player.c $(CFLAGS)

collision.o: ${SRC}collision.c
	$(CC) -c ${SRC}collision.c $(CFLAGS)
#	$(WIN) -c ${SRC}collision.c $(CFLAGS)

enemy.o: ${SRC}enemy.c
	$(CC) -c ${SRC}enemy.c $(CFLAGS)
#	$(WIN) -c ${SRC}enemy.c $(CFLAGS)

missile.o: ${SRC}missile.c
	$(CC) -c ${SRC}missile.c $(CFLAGS)
#	$(WIN) -c ${SRC}missile.c $(CFLAGS)

level.o: ${SRC}level.c
	$(CC) -c ${SRC}level.c $(CFLAGS)
#	$(WIN) -c ${SRC}level.c $(CFLAGS)

missile_enemy.o: ${SRC}missile_enemy.c
	$(CC) -c ${SRC}missile_enemy.c $(CFLAGS)
#	$(WIN) -c ${SRC}missile_enemy.c $(CFLAGS)

health_bar.o: ${SRC}health_bar.c
	$(CC) -c ${SRC}health_bar.c $(CFLAGS)
#	$(WIN) -c ${SRC}health_bar.c $(CFLAGS)

party.o: ${SRC}party.c
	$(CC) -c ${SRC}party.c $(CFLAGS)
#	$(WIN) -c ${SRC}party.c $(CFLAGS)

menu.o: ${SRC}menu.c
	$(CC) -c ${SRC}menu.c $(CFLAGS)
#	$(WIN) -c ${SRC}menu.c $(CFLAGS)

bonus.o: ${SRC}bonus.c
	$(CC) -c ${SRC}bonus.c $(CFLAGS)
#	$(WIN) -c ${SRC}menu.c $(CFLAGS)

nuke.o: ${SRC}nuke.c
	$(CC) -c ${SRC}nuke.c $(CFLAGS)
#	$(WIN) -c ${SRC}menu.c $(CFLAGS)

keyboard.o: ${SRC}keyboard.c
	$(CC) -c ${SRC}keyboard.c $(CFLAGS)
#	$(WIN) -c ${SRC}menu.c $(CFLAGS)

end.o: ${SRC}end.c
	$(CC) -c ${SRC}end.c $(CFLAGS)
#	$(WIN) -c ${SRC}menu.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~
	rm -f projet
#	rm -f docs/
#	rm -f projet.exe