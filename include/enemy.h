#include <MLV/MLV_all.h>


void init_enemy(Enemy** enemies, int* nb_enemy, int x, int y);
void update_enemy(Enemy** enemies, int* nb_enemy, MLV_Image** explosion_images, MLV_Sound** sound);
void add_enemy(Enemy** enemies, Enemy enemy, int* nb_enemy);
void remove_enemy(Enemy** enemies, int index, int* nb_enemy);
void draw_enemy(Enemy* enemy);
void movement_enemy(Enemy* enemy);