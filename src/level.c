
#include <stdio.h>
#include "../include/struct.h"
#include "../include/enemy.h"
#include "../include/const.h"
#include "../include/missile_enemy.h"


void update_level(char*** waves, int* nb_wave, int* current_waves, Enemy** enemies , int* nb_enemy, int* quit){
    /*if(ennemy_nb == 0) {
        for(int i = 0; i <)
        create_ennemies(waves[current_wave]);
        current_wave++
    }*/
        /*while (fgets(line, 100, fptr) != NULL) {
        int num_enemies = 0;
        for (int i = *wave; line[i] != '\0'; i++) {
            if(line[i] == 'X' || line[i] == '0'){
                num_enemies++;
            }
        }*/
        int y = -ENEMY_W;
        
        int line_size;
        for(int i = *current_waves; i < *nb_wave; i++){
            line_size = strlen((*waves)[i]);
            int x = (WIDTH - line_size * ENEMY_W) / 2;
            for(int j = 0; j < line_size; j++){
                //printf("%c", (*waves)[i][j]);
                if((*waves)[i][j] == 'X'){
                    init_enemy(enemies, nb_enemy, x ,y, 0);
                     x += ENEMY_W;
                }else if ((*waves)[i][j] == '0'){
                     x += ENEMY_W;
                }else if ((*waves)[i][j] == 'V'){
                    init_enemy(enemies, nb_enemy, x ,y, 1);
                     x += ENEMY_W;
                }else if ((*waves)[i][j] == 'F'){
                    *quit =1;
                    return;
                }else if ((*waves)[i][j] == '-'){
                    y += ENEMY_W;
                    *current_waves = i+1;
                    return;
                }
            }
            y += ENEMY_W;
            //printf("\n"); 

        }
}
void init_level(char*** waves, int* nb_wave, int* current_wave) {
    
    FILE *fptr;
    
    // Ouvre le fichier en mode lecture
    fptr = fopen("./level/level1.txt", "r");

    // Vérifie si le fichier a été ouvert avec succès
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    *waves = (char**)malloc(0);


    // Lit le fichier ligne par ligne jusqu'à la fin du fichier
    char line[100];
    while (fgets(line, 100, fptr) != NULL) {
        // Ajoute la ligne au tableau de vagues
        *waves = (char**)realloc(*waves, (*nb_wave + 1) * sizeof(char*));
        //printf("Realloc %d char*\n", *nb_wave+1);
        if(*waves == NULL) {
            printf("Waves add error...\n");
            return;
        }
        (*waves)[*nb_wave] = (char*)malloc(strlen(line)+1 * sizeof(char));

        if((*waves)[*nb_wave] == NULL) {
            printf("Memory allocation error...\n");
            return;
        }
        if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
        strcpy((*waves)[*nb_wave], line);
        //printf("malloc %ld char : %s (= %s)\n", strlen(line)+1, line, (*waves)[*nb_wave]);

        *nb_wave = (*nb_wave) + 1;       
    }

    
  

    // Ferme le fichier
    fclose(fptr);
}