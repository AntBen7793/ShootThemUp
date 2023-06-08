#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/player.h"
#include "../include/const.h"

Player init_player()
{
    Player player;
    player.x = (WIDTH / 2)-35;
    player.y = 500;
    player.dx = 0;
    player.dy = 0;
    player.width = 70;
    player.speed = 5;
    player.life = 100;
    player.shield = 0;
    player.shot = 0;
    player.nuke = 0;
    /* sprites */
    player.sprite = MLV_load_image("./img/state1_player.png");
    player.sprite_right = MLV_load_image("./img/state1_right_player.png");
    player.sprite_left = MLV_load_image("./img/state1_left_player.png");
    player.sprite_forward = MLV_load_image("./img/state0_player.png");
    player.sprite_shield = MLV_load_image("./img/shield_active_state0.png");

    // MLV_resize_image(player.sprite_left, player.width, player.width);
    // MLV_resize_image(player.sprite_right, player.width, player.width);
    // MLV_resize_image(player.sprite_forward, player.width, player.width);

    return player;
}

void update_player(Player *player)
{
    player->x += player->dx;
    player->y += player->dy;

    check_keyboard(player);
    check_player_collision_border(player);
}

void draw_player(Player *player)
{

    if (player->dx > 0)
        MLV_draw_image(player->sprite_right, player->x, player->y);
    else if (player->dx < 0)
        MLV_draw_image(player->sprite_left, player->x, player->y);
    else if (player->dy < 0)
        MLV_draw_image(player->sprite_forward, player->x, player->y);
    else
    {
        MLV_draw_image(player->sprite, player->x, player->y);
    }
    if (player->shield > 0)
    {
        MLV_resize_image(player->sprite_shield, player->width + 30, player->width + 30);
        MLV_draw_image(player->sprite_shield, player->x - 15, player->y - 15);
    }
    // MLV_draw_rectangle(player->x, player->y, player->width, player->width, MLV_COLOR_BLUE);
}

void check_keyboard(Player *player)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED)
    {
        player->dx = player->speed;
    }
    else if (MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED)
    {
        player->dx = -player->speed;
    }
    else
    {
        player->dx = 0;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED)
    {
        player->dy = player->speed;
    }
    else if (MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED)
    {
        player->dy = -player->speed;
    }
    else
    {
        player->dy = 0;
    }
}
void check_player_collision_border(Player *player)
{
    if (player->x >= WIDTH - player->width)
    {
        player->x = WIDTH - player->width;
    }
    if (player->x <= 0)
    {
        player->x = 0;
    }
    if (player->y <= 0)
    {
        player->y = 0;
    }
    if (player->y >= HEIGHT - player->width)
    {
        player->y = HEIGHT - player->width;
    }
}