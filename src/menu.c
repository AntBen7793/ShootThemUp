
#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include "../include/menu.h"
#include "../include/const.h"
#include "../include/party.h"

void draw_button(int x, int y, int w, int h, char *text, MLV_Font *font, int mouse_x, int mouse_y)
{
    int text_width, text_height;
    MLV_get_size_of_text(text, &text_width, &text_height);
    MLV_Color text_color = MLV_COLOR_WHITE;

    if (
        mouse_x >= x && mouse_x <= x + w &&
        mouse_y >= y && mouse_y <= y + h)
    {
        text_color = MLV_COLOR_ORANGE1;
    }
    MLV_draw_text_box_with_font(x, y, w, h, text, font, 1, MLV_COLOR_WHITE, text_color, MLV_COLOR_NAVY_BLUE, MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_TEXT_CENTER);
}

void init_menu()
{
    int mouse_x, mouse_y;
    int button_width = 220;
    int button_height = 70;
    int button_x = WIDTH / 2 - button_width / 2;
    int button_y = 400;

    int button_y2 = 500;

    int button_y3 = 600;
    MLV_Font *font = MLV_load_font("./font/ARCADECLASSIC.ttf", 50);
    double accum;
    int quit = 0;
    struct timespec last, new;
    int y = 0;
    int y2 = 0;
    int x = 0;
    MLV_Image *background = MLV_load_image("./img/sea_.png");
    MLV_Image *cloud = MLV_load_image("./img/cloud.png");
    MLV_Image *logo = MLV_load_image("./img/topgun.png");
    MLV_resize_image(cloud, WIDTH, HEIGHT);
    MLV_resize_image(logo, 600, 200);
    MLV_resize_image(background, WIDTH, HEIGHT);
    MLV_init_audio();
    MLV_Music *music = MLV_load_music("sound/music.mp3");
    MLV_play_music(music, 1.0, -1);
    while (!quit)
    {
        /* Get the time in nanoseconds at the frame beginning */
        clock_gettime(CLOCK_REALTIME, &last);
        /* Display of the current frame */
        /* THIS FUNCTION CALL A SINGLE TIME MLV_actualize_window */
        // draw_window(&param, &grid);
        MLV_clear_window(MLV_COLOR_SKY_BLUE);
        y = y + 3;
        y2 = y2 + 1;
        if (y >= HEIGHT)
        {
            y = 0;
        }
        if (y2 >= HEIGHT)
        {
            y2 = 0;
        }
        MLV_draw_image(background, x, y);
        MLV_draw_image(background, x, y - HEIGHT);
        MLV_draw_image(cloud, x, y2);
        MLV_draw_image(cloud, x, y2 - HEIGHT);
        MLV_draw_image(logo, 100, 100);
        draw_button(button_x, button_y, button_width, button_height, "Play", font, mouse_x, mouse_y);
        draw_button(button_x, button_y2, button_width, button_height, "Setting", font, mouse_x, mouse_y);
        draw_button(button_x, button_y3, button_width, button_height, "Leave", font, mouse_x, mouse_y);
        MLV_get_mouse_position(&mouse_x, &mouse_y);
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
            mouse_x >= button_x && mouse_x <= button_x + button_width &&
            mouse_y >= button_y && mouse_y <= button_y + button_height)
        {
            MLV_stop_music();
            init_party();
            /*Stop update menu until update party is finish*/
            MLV_play_music(music, 1.0, -1);
        }
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
            mouse_x >= button_x && mouse_x <= button_x + button_width &&
            mouse_y >= button_y3 && mouse_y <= button_y3 + button_height)
        {
            return;
        }
        /* Get the time in nanoseconds at the frame ending */
        clock_gettime(CLOCK_REALTIME, &new);

        /* We compute here the time spent for the current frame */
        accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / 1000000000);

        /* We force here to wait if the frame was too short */
        if (accum < (1.0 / 48.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 40.0) - accum) * 1000));
        }

        MLV_actualise_window();
    }
    MLV_free_image(cloud);
    MLV_free_image(background);
    MLV_stop_music();
    MLV_free_music(music);
}