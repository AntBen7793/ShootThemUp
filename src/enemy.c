#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/enemy.h"

void init_enemy(Enemy** enemies, int* nb_enemy, int x, int y){
    Enemy enemy;
    enemy.x = x;
    enemy.width = 100;
    enemy.y = y;
    enemy.speed = 2;
    enemy.sprite = MLV_load_image("./img/state1_enemy.png");
     add_enemy(enemies, enemy, nb_enemy);
}

void update_enemy(Enemy** enemies, int nb_enemy){
    //check_player_collision_border(enemy);
    for(int i = 0; i < nb_enemy; i++){
        (*enemies)[i].y = (*enemies)[i].y + (*enemies)[i].speed;       
        draw_enemy(&((*enemies)[i]));
    }   
}

void draw_enemy(Enemy* enemy){

        MLV_draw_image((*enemy).sprite, (*enemy).x, (*enemy).y);
        MLV_draw_rectangle((*enemy).x, (*enemy).y, (*enemy).width, (*enemy).width, MLV_COLOR_RED);
}

void add_enemy(Enemy** enemies, Enemy enemy, int* nb_enemy){
    *enemies = (Enemy*)realloc(*enemies, (*nb_enemy + 1) * sizeof(Enemy));
    if(*enemies == NULL) {
        printf("Enemy add error...\n");
        return;
    }
    (*enemies)[*nb_enemy] = enemy;
    *nb_enemy = (*nb_enemy) + 1;

    
    
}

void remove_enemy(Enemy** enemies, int index, int* nb_enemy) {
     
    if (index < 0 || index >= *nb_enemy) {
        printf("Index out of bounds error...\n");
        return;
    }

    for (int i = index; i < *nb_enemy - 1; i++) {
        (*enemies)[i] = (*enemies)[i+1];
    }
    (*nb_enemy)--;
   
    Enemy* temp = (Enemy*)realloc(*enemies, *nb_enemy * sizeof(Enemy));
    if (temp == NULL && *nb_enemy > 0) {
        printf("Memory allocation error while removing enemy.\n");
        return;
    }
    *enemies = temp;
}