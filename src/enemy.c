#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/enemy.h"




void init_enemy(Enemy** enemies, int* nb_enemy, int x, int y){
    Enemy enemy;
    enemy.x = x;
    enemy.width = 70;
    enemy.y = y;
    enemy.speed = 2;
    enemy.explosion_state = 0;
    enemy.life = 100;
    enemy.sprite = MLV_load_image("./img/state1_enemy.png");
    MLV_resize_image(enemy.sprite, enemy.width, enemy.width);
    
    add_enemy(enemies, enemy, nb_enemy);
}

/*void update_enemy(Enemy** enemies, int* nb_enemy){
    //check_player_collision_border(enemy);
    //sleep(0.5);
    for(int i = 0; i < *nb_enemy; i++){
        (*enemies)[i].y = (*enemies)[i].y + (*enemies)[i].speed;          
        draw_enemy(&((*enemies)[i]));
        if((*enemies)[i].life <= 0){
            //printf(" life => %d\n", (*enemies)[i].life);
            (*enemies)[i].explosion_state++;
            switch ((*enemies)[i].explosion_state)
            {
            case 0:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state0.png");
                break;
            case 1:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state1.png");
                break;  
            case 2:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state2.png");
                break;
            case 3:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state3.png");
                break;
            case 4:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state4.png");
                break;
            case 5:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state5.png");
                break;
            case 6:
                (*enemies)[i].sprite = MLV_load_image("./img/explosion_state6.png");
                break;
            
            default:
                //(*enemies)[i].sprite = MLV_load_image("./img/explosion_state0.png");
                break;
            }
            
            if((*enemies)[i].explosion_state >=10){
                remove_enemy(enemies, i, nb_enemy);
            }
        }
    }   
}*/


void update_enemy(Enemy** enemies, int* nb_enemy, MLV_Image** explosion_images) {
    for (int i = 0; i < *nb_enemy; i++) {
        Enemy* enemy = &((*enemies)[i]);
        enemy->y += enemy->speed;
        draw_enemy(enemy);
        if (enemy->life <= 0) {
            enemy->explosion_state++;
            if (enemy->explosion_state < 6) {
                enemy->sprite = explosion_images[enemy->explosion_state];
            } 
            if(enemy->explosion_state >8){
                remove_enemy(enemies, i, nb_enemy);
                i--;
            }
        }
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