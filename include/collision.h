


int check_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
void check_collision_enemy_missile(Enemy** enemies, Missile** missiles, int* nb_missile, int* nb_enemy, MLV_Sound** sound, double* effect_volume);
void check_collision_enemy_missile_player(Player* player, Missile_enemy** missiles_enemy, int* nb_missile_enemy, int* quit, MLV_Sound** sound, double* effect_volume);
void check_collision_enemy(Player* player, Enemy** enemies, int* nb_enemy, int* quit,MLV_Sound** sound, double* effect_volume);
void check_collision_bonus_player(Player* player, Bonus** bonus_list, int* nb_bonus, MLV_Sound** sound, double* effect_volume);
void check_collision_nuke_enemy(Nuke* nuke,Enemy **enemies, int *nb_enemy, MLV_Sound *sound, double *effect_volume);
