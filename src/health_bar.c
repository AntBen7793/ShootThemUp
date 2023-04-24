#include <MLV/MLV_all.h>
#include "../include/const.h"
#include "../include/struct.h"
#include "../include/player.h"

void draw_health_bar(int x, int y, int width, int height, Player *player, MLV_Image *hud, MLV_Image *shield_icon,MLV_Image *bomb_icon, MLV_Image *nuke_icon,MLV_Font *font_hud, MLV_Image *filtre)
{
    int bar_width = (int)((float)player->life / 100 * (float)width);
    int x2 = 50;
    int y2 = 750; 
    // Draw background
    // MLV_draw_rectangle(x, y, width, height, MLV_COLOR_GRAY);
    MLV_draw_image(hud, x, y);
    MLV_draw_image(shield_icon, x + 20, y + 20);
    char text_shield[10];
    snprintf(text_shield, sizeof(text_shield), "%d", player->shield);
    MLV_draw_text_with_font(x + 60, y + 20, text_shield, font_hud, MLV_COLOR_RED);


    MLV_draw_image(bomb_icon, x + 80, y + 25);
    char text_bomb[10];
    snprintf(text_bomb, sizeof(text_bomb), "%d", player->shot);
    MLV_draw_text_with_font(x + 110, y + 20, text_bomb, font_hud, MLV_COLOR_RED);

    MLV_draw_image(nuke_icon, x + 130, y + 25);
    char text_nuke[10];
    snprintf(text_nuke, sizeof(text_nuke), "%d", player->nuke);
    MLV_draw_text_with_font(x + 165, y + 20, text_nuke, font_hud, MLV_COLOR_RED);

    // Draw health bar
    MLV_draw_rectangle(x2-1, y2-1, width+2, height+2, MLV_COLOR_BLACK);
    if (player->life >= 50) {
        MLV_draw_filled_rectangle(x2, y2, bar_width, height, MLV_COLOR_GREEN);
    } else if (player->life > 0) {
        MLV_draw_filled_rectangle(x2, y2, bar_width, height, MLV_COLOR_ORANGE);
        MLV_draw_line(x2 + bar_width, y2, x2 + bar_width, y2 + height, MLV_COLOR_BLACK);
    } else {
        MLV_draw_filled_rectangle(x2, y2, 0, height, MLV_COLOR_RED);
    }
    MLV_draw_image(filtre, x+25, y+20);
}
