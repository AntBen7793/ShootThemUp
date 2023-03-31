#include "../include/struct.h"
#include "../include/missile.h"

#include <string.h>


void init_missile(Missile** missiles, int* nb_missile, int x, int y){
    Missile missile;
    missile.x = x;
    missile.y = y;
    missile.width = 10;
    missile.height = 30;
    missile.speed = 15;
    missile.dmg = 50;
    missile.sprite = MLV_load_image("./img/bullet.png");
    add_missile(missiles, missile, nb_missile);
}

void update_missile(Missile** missiles, int nb_missile){  
   for(int i = 0; i < nb_missile; i++){
        (*missiles)[i].y = (*missiles)[i].y - (*missiles)[i].speed;
        draw_missile(&((*missiles)[i]));
    }    
}

void draw_missile(Missile* missile){
    MLV_draw_image((*missile).sprite, (*missile).x, (*missile).y);
    MLV_draw_rectangle((*missile).x, (*missile).y, (*missile).width, (*missile).height, MLV_COLOR_RED); 
}

void add_missile(Missile** missiles, Missile missile, int* nb_missile){
    *missiles = (Missile*)realloc(*missiles, (*nb_missile + 1) * sizeof(Missile));
    if(*missiles == NULL) {
        printf("Missile add error...\n");
        return;
    }
    (*missiles)[*nb_missile] = missile;
    *nb_missile = (*nb_missile) + 1;   
}

void remove_missile(Missile** missiles, int index, int* nb_missile) {
     
    if (index < 0 || index >= *nb_missile) {
        printf("Index out of bounds error...\n");
        return;
    }

    for (int i = index; i < *nb_missile - 1; i++) {
        (*missiles)[i] = (*missiles)[i+1];
    }
    (*nb_missile)--;
   
    Missile* temp = (Missile*)realloc(*missiles, *nb_missile * sizeof(Missile));
    if (temp == NULL && *nb_missile > 0) {
        printf("Memory allocation error while removing missile.\n");
        return;
    }
    *missiles = temp;
}

int check_missile_collision_border(Missile* missile){
    if(missile->y <= 0){
        return 1;
    }else{
        return 0;
    }
}


