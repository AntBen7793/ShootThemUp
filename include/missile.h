#include <MLV/MLV_all.h>


void init_missile(Missile** missiles, int* nb_missile, int x, int y, int type);
void draw_missile(Missile* missile);
void update_missile(Missile** missiles, int nb_missile);
void add_missile(Missile** missiles, Missile missile, int* nb_missile);
void remove_missile(Missile** missiles, int i, int* nb_missile);
int check_missile_collision_border(Missile* missile);