
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/const.h"
#include "../include/struct.h"
#include "../include/player.h"
#include "../include/menu.h"

#include "../include/end.h"


void draw_info_case(int x, int y, int w, int h, char *text, MLV_Font *font)
{
    int text_width, text_height;
    MLV_get_size_of_text(text, &text_width, &text_height);
    MLV_draw_text_box_with_font(x, y, w, h, text, font, 1, MLV_COLOR_WHITE, MLV_COLOR_ORANGE1, MLV_COLOR_NAVY_BLUE, MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_TEXT_CENTER);
}

void init_end(int *win, int *finish, MLV_Font *font_end, MLV_Font *font_hud, int width, int *mouse_x, int *mouse_y, Player * player, int* enemy_killed)
{
    draw_button(290, 600, 220, 70, "LEAVE", font_hud, *mouse_x, *mouse_y);
    MLV_draw_filled_rectangle(WIDTH / 2 - 500 / 2, 260, 500, 300, MLV_COLOR_NAVY_BLUE);
    MLV_draw_rectangle(WIDTH / 2 - 500 / 2, 260, 500, 300, MLV_COLOR_WHITE);


    
    MLV_draw_text_with_font(180, 280, "Life remaining", font_hud, MLV_COLOR_WHITE);
    char life_text[55];
    snprintf(life_text, sizeof(life_text), "%d", player->life);
    MLV_draw_text_with_font(550, 280, life_text, font_hud, MLV_COLOR_WHITE);

    MLV_draw_text_with_font(180, 320, "Bonus remaining", font_hud, MLV_COLOR_WHITE);
    char bonus_text[55];
    snprintf(bonus_text, sizeof(bonus_text), "%d", player->nuke+player->shield+player->shot);
    MLV_draw_text_with_font(550, 320, bonus_text, font_hud, MLV_COLOR_WHITE);

    MLV_draw_text_with_font(180, 360, "Enemy killed", font_hud, MLV_COLOR_WHITE);
    char enemy_text[55];
    snprintf(enemy_text, sizeof(enemy_text), "%d", *enemy_killed);
    MLV_draw_text_with_font(550, 360, enemy_text, font_hud, MLV_COLOR_WHITE);

    if (*win == 1)
    {
        // MLV_draw_text_with_font(290, 500, "WIN", font_end, MLV_COLOR_ORANGE1);
        draw_info_case(WIDTH / 2 - width / 2, 150, 300, 70, "WIN", font_end);
        // MLV_draw_filled_rectangle(x, y, w, h, MLV_COLOR_NAVY_BLUE);
    }
    else
    {
        draw_info_case(WIDTH / 2 - width / 2, 150, 300, 70, "LOOSE", font_end);
    }
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
        *mouse_x >= 290 && *mouse_x <= 290 + 220 &&
        *mouse_y >= 600 && *mouse_y <= 600 + 70)
    {
        *finish = 1;
    }
}