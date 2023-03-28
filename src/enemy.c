#include "../include/enemy.h"
#include <MLV/MLV_all.h>
#include "../include/const.h"

Enemy init_enemy(int x){
    Enemy enemy;
    enemy.x = x;
    enemy.width = 50;
    enemy.y = enemy.width;
    enemy.speed = 5;
 
 return enemy;
}

void update_enemy(Enemy* enemy){
    //enemy->y++;
    //check_player_collision_border(enemy);
}