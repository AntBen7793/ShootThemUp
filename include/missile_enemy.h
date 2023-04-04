#include <MLV/MLV_all.h>


void init_missile_enemy(Missile_enemy** missiles_enemy, int* nb_missile_enemy, int x, int y);
void draw_missile_enemy(Missile_enemy* missile_enemy);
void update_missile_enemy(Missile_enemy** missiles_enemy, int nb_missile_enemy);
void add_missile_enemy(Missile_enemy** missiles_enemy, Missile_enemy missile_enemy, int* nb_missile_enemy);
void remove_missile_enemy(Missile_enemy** missiles_enemy, int i, int* nb_missile_enemy);
int check_missile_enemy_collision_border(Missile_enemy* missile_enemy);