#include <MLV/MLV_all.h>

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int width;
    int speed;
    int life;
    MLV_Image * sprite;
    MLV_Image * sprite_left;
    MLV_Image * sprite_right;
    MLV_Image * sprite_forward;
} Player;

Player init_player();
void update_player(Player* player);
void check_player_collision_border(Player* player);
void draw_player(Player* player);
void check_keyboard(Player* player);
