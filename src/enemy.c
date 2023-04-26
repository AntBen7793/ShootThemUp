#include <MLV/MLV_all.h>
#include <math.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/enemy.h"
#include "../include/missile_enemy.h"

#define PI 3.14159

void init_enemy(Enemy** enemies, int* nb_enemy, int x, int y, int type){
    Enemy enemy;
    enemy.center=x;
    enemy.x = x;
    enemy.width = 70;
    enemy.y = y;
    enemy.speed = 1;
    enemy.explosion_state = 0;
    enemy.life = 100;
    enemy.type = type;
    enemy.cooldown = 0;
    enemy.sprite = MLV_load_image("./img/state1_enemy.png");
    
    
    MLV_resize_image(enemy.sprite, enemy.width, enemy.width);
    add_enemy(enemies, enemy, nb_enemy);
}

int check_enemy_collision_border(Enemy* enemy){
    if(enemy->y >= HEIGHT){
        return 1;
    }else{
        return 0;
    }
}

void update_enemy(Enemy** enemies, int* nb_enemy, MLV_Image** explosion_images,MLV_Sound** sound, Missile_enemy** missiles_enemy, Stats * stats, int* nb_missile_enemy,double* effect_volume) {
    for (int i = 0; i < *nb_enemy; i++) {
        Enemy* enemy = &((*enemies)[i]);

        movement_enemy(enemy);
        shoot_enemy(enemy, missiles_enemy, nb_missile_enemy);
        draw_enemy(enemy);
   
       
        if (enemy->life <= 0) {
            enemy->explosion_state++;
            
            if (enemy->explosion_state < 18 && enemy->explosion_state%2 == 0) {
                enemy->sprite = explosion_images[enemy->explosion_state -(enemy->explosion_state /2) ];
                MLV_resize_image(enemy->sprite, enemy->width, enemy->width);
            }
            if(enemy->explosion_state == 1){
                MLV_play_sound((*sound), *effect_volume);
            }
            if(enemy->explosion_state >20){
                remove_enemy(enemies, i, nb_enemy);
                stats->nb_enemy_killed ++;
                i--;
            }
        }
    }
}
void shoot_enemy(Enemy* enemy,Missile_enemy** missiles_enemy, int* nb_missile_enemy){
    switch (enemy->type)
            {
            case 0:
                 if(enemy->cooldown >= 60){
                //init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+(enemy->width/2), enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+10, enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+ ((enemy->width) - 20), enemy->y);
                enemy->cooldown = 0;
                }else{
                enemy->cooldown ++;
                }
                 break;
            case 1:
                if(enemy->cooldown >= 30){
                //init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+(enemy->width/2), enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+10, enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+ ((enemy->width) - 20), enemy->y);
                enemy->cooldown = 0;
                }else{
                enemy->cooldown ++;
                }
                 break;
            case 3:
                if(enemy->cooldown >= 55){
                //init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+(enemy->width/2), enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+10, enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+ ((enemy->width) - 20), enemy->y);
                enemy->cooldown = 0;
                }else{
                enemy->cooldown ++;
                }
                 break;
            case 4:
                if(enemy->cooldown >= 55){
                //init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+(enemy->width/2), enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+10, enemy->y);
                init_missile_enemy(missiles_enemy, nb_missile_enemy, (enemy->x)+ ((enemy->width) - 20), enemy->y);
                enemy->cooldown = 0;
                }else{
                enemy->cooldown ++;
                }
                 break;
            
            default:

                break;
            }
}
void movement_enemy(Enemy* enemy){
    //printf("test => %d\n", enemy->type);
    switch (enemy->type)
            {
            case 0:
                 enemy->y += enemy->speed;
                 break;
            case 1:
                 enemy->y += enemy->speed*2;
                 break;
            case 2:
                 enemy->y += enemy->speed*10;
                 break;
            case 3:
                 enemy->y += enemy->speed*2;
                 enemy->x = enemy->center -  WIDTH/14 * sin(2*PI*enemy->y/HEIGHT*5);
                 break;
            case 4:
                 enemy->y += enemy->speed*2;
                 enemy->x = enemy->center +  WIDTH/14 * sin(2*PI*enemy->y/HEIGHT*5);
                 break;
            default:

                break;
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


