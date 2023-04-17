void update_bonus(Bonus **bonus_list, int nb_bonus, MLV_Image **bonus_images);
void add_bonus(Bonus **bonus_list, Bonus bonus, int *nb_bonus);
void init_bonus(Bonus **bonus_list, int *nb_bonus, int x, int y, int type);
void draw_bonus(Bonus* bonus);
void remove_bonus(Bonus** bonus_list, int index, int* nb_bonus);
void movement_bonus(Bonus* bonus);
int check_bonus_collision_border(Bonus* bonus);