#include "../include/const.h"
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/missile.h"
#include "../include/missile_enemy.h"
#include "../include/enemy.h"
#include "../include/player.h"


int check_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2){
    if(x < x2 + width2 &&
   x + width > x2 &&
   y < y2 + height2 &&
   height + y > y2){
        return 1;
    }
    return 0;
}

void check_collision_enemy_missile(Enemy** enemies, Missile** missiles, int* nb_missile, int* nb_enemy, MLV_Sound** sound, double* effect_volume) {

    for (int i = 0; i < *nb_missile; i++) {
        if (check_missile_collision_border(&((*missiles)[i])) == 1) {
            remove_missile(missiles, i, nb_missile);
            break;
        }  
        for (int j = 0; j < *nb_enemy; j++) {
            if (check_collision((*missiles)[i].x, (*missiles)[i].y, (*missiles)[i].width, (*missiles)[i].height, (*enemies)[j].x, (*enemies)[j].y, (*enemies)[j].width, (*enemies)[j].width) == 1) {
                
                 MLV_play_sound((*sound), *effect_volume);
                (*enemies)[j].life = (*enemies)[j].life - (*missiles)[i].dmg;
                //remove_enemy(enemies, j, nb_enemy);
                remove_missile(missiles, i, nb_missile);
                
                //printf("life => %d\n", (*enemies)[j].life);
                
                break;
            }
        }
    }
}
void check_collision_enemy_missile_player(Player* player, Missile_enemy** missiles_enemy, int* nb_missile_enemy, int* quit, MLV_Sound** sound, double* effect_volume) {

    for (int i = 0; i < *nb_missile_enemy; i++) {
        if (check_missile_enemy_collision_border(&((*missiles_enemy)[i])) == 1) {
            remove_missile_enemy(missiles_enemy, i, nb_missile_enemy);
            break;
        }
        if(check_collision((*missiles_enemy)[i].x, (*missiles_enemy)[i].y, (*missiles_enemy)[i].width, (*missiles_enemy)[i].height, (*player).x, (*player).y, (*player).width, (*player).width) == 1){
             MLV_play_sound((*sound), *effect_volume);
            (*player).life = (*player).life - (*missiles_enemy)[i].dmg;
            if ((*player).life < 0) (*player).life = 0;
            remove_missile_enemy(missiles_enemy, i, nb_missile_enemy);
        }
        if((*player).life <= 0){
            printf("GAME OVER");
            //(*player).life = 100;
            (*quit) = 1;
        }
    }
}
