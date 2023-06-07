#include "../include/struct.h"
#include "../include/missile_enemy.h"
#include "../include/const.h"
#include <string.h>


void init_missile_enemy(Missile_enemy** missiles_enemy, int* nb_missile_enemy, int x, int y){
    Missile_enemy missile_enemy;
    missile_enemy.x = x;
    missile_enemy.y = y;
    missile_enemy.width = 10;
    missile_enemy.height = 30;
    missile_enemy.speed = 10;
    missile_enemy.dmg = 34;
    missile_enemy.sprite = MLV_load_image("./img/bullet.png");
    add_missile_enemy(missiles_enemy, missile_enemy, nb_missile_enemy);
}

void update_missile_enemy(Missile_enemy** missiles_enemy, int nb_missile_enemy){  
   for(int i = 0; i < nb_missile_enemy; i++){
    
        (*missiles_enemy)[i].y = (*missiles_enemy)[i].y + (*missiles_enemy)[i].speed;
    
        
        draw_missile_enemy(&((*missiles_enemy)[i]));
    }    
}

void draw_missile_enemy(Missile_enemy* missile_enemy){
    MLV_draw_image((*missile_enemy).sprite, (*missile_enemy).x, (*missile_enemy).y);
    //MLV_draw_rectangle((*missile_enemy).x, (*missile_enemy).y, (*missile_enemy).width, (*missile_enemy).height, MLV_COLOR_RED); 
}

void add_missile_enemy(Missile_enemy** missiles_enemy, Missile_enemy missile_enemy, int* nb_missile_enemy){
    *missiles_enemy = (Missile_enemy*)realloc(*missiles_enemy, (*nb_missile_enemy + 1) * sizeof(Missile_enemy));
    if(*missiles_enemy == NULL) {
        printf("Missile_enemy add error...\n");
        return;
    }
    (*missiles_enemy)[*nb_missile_enemy] = missile_enemy;
    *nb_missile_enemy = (*nb_missile_enemy) + 1;   
}

void remove_missile_enemy(Missile_enemy** missiles_enemy, int index, int* nb_missile_enemy) {
     
    if (index < 0 || index >= *nb_missile_enemy) {
        printf("Index out of bounds error...\n");
        return;
    }

    for (int i = index; i < *nb_missile_enemy - 1; i++) {
        (*missiles_enemy)[i] = (*missiles_enemy)[i+1];
    }
    (*nb_missile_enemy)--;
   
    Missile_enemy* temp = (Missile_enemy*)realloc(*missiles_enemy, *nb_missile_enemy * sizeof(Missile_enemy));
    if (temp == NULL && *nb_missile_enemy > 0) {
        printf("Memory allocation error while removing missile_enemy.\n");
        return;
    }
    *missiles_enemy = temp;
}

int check_missile_enemy_collision_border(Missile_enemy* missile_enemy){
    if(missile_enemy->y >= HEIGHT){
        return 1;
    }else{
        return 0;
    }
}


