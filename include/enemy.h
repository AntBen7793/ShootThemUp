

void init_enemy(Enemy** enemies, int* nb_enemy, int x, int y);
void update_enemy(Enemy** enemies, int nb_enemy);
void add_enemy(Enemy** enemies, Enemy enemy, int* nb_enemy);
void remove_enemy(Enemy** enemies, int index, int* nb_enemy);
void draw_enemy(Enemy* enemy);