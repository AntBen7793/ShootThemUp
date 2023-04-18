#include <MLV/MLV_all.h>


typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int width;
    int speed;
    int life;
    int shield;
    int shot;
    MLV_Image * sprite;
    MLV_Image * sprite_left;
    MLV_Image * sprite_right;
    MLV_Image * sprite_forward;
    MLV_Image * sprite_shield;
} Player;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    int dmg;
    int type;
    MLV_Image * sprite;
} Missile;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    int dmg;
    MLV_Image * sprite;
} Missile_enemy;

typedef struct {
    int x;
    int y;
    int width;
    int speed;
    int type;
    int animation_state;
    MLV_Image * sprite;
} Bonus;

typedef struct {
    int x;
    int y;
    int width;
    int speed;
    int life;
    int type;
    int cooldown;
    int explosion_state;
    MLV_Image * sprite;
} Enemy;