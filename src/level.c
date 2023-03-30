
#include <stdio.h>
#include "../include/struct.h"
#include "../include/enemy.h"
#include "../include/const.h"

void init_level(Enemy** enemies, int* nb_enemy){
    int x = 0;
    int y = 10;
    FILE *fptr;

    // Ouvre le fichier en mode lecture
    fptr = fopen("./level/level1.txt", "r");

    // Vérifie si le fichier a été ouvert avec succès
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    // Lit le fichier ligne par ligne jusqu'à la fin du fichier
    char line[100];
    while (fgets(line, 100, fptr) != NULL) {
    x = -((ENEMY_W * strlen(line)) / 2) + (WIDTH / 2);
    int length;
    for (int i = 0; line[i] != '\0'; i++) {
        length = i + 1;
    }
    for (int i = 0; i < length; i++) {
        if(line[i] == 'X'){
            init_enemy(enemies, nb_enemy, x, y);
            x += ENEMY_W;
        }else if(line[i] == '0'){
            x += ENEMY_W;
        }
    }
    y+=100;
    
}

    // Ferme le fichier
    fclose(fptr);
}