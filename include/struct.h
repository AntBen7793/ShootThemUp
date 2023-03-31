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

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    int dmg;
    MLV_Image * sprite;
} Missile;

typedef struct {
    int x;
    int y;
    int width;
    int speed;
    int life;
    int explosion_state;
    MLV_Image * sprite;
} Enemy;