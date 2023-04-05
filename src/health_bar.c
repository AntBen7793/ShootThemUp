#include "../include/const.h"
#include <MLV/MLV_all.h>

void draw_health_bar(int x, int y, int width, int height, int health) {
    int bar_width = (int)((float)health / 100 * (float)width);

    // Draw background
    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_GRAY);

    // Draw health bar
    if (health >= 50) {
        MLV_draw_filled_rectangle(x, y, bar_width, height, MLV_COLOR_GREEN);
    } else if (health > 0) {
        MLV_draw_filled_rectangle(x, y, bar_width, height, MLV_COLOR_ORANGE);
        MLV_draw_line(x + bar_width, y, x + bar_width, y + height, MLV_COLOR_BLACK);
    } else {
        MLV_draw_filled_rectangle(x, y, 0, height, MLV_COLOR_RED);
    }
}
