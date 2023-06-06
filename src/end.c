

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <time.h>
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
void display_info(int x, int y, char *text, int value, MLV_Font *font_hud)
{

    MLV_draw_text_with_font(x, y, text, font_hud, MLV_COLOR_WHITE);
    char text_value[10];
    snprintf(text_value, sizeof(text_value), "%d", value);
    MLV_draw_text_with_font(x + 370, y, text_value, font_hud, MLV_COLOR_WHITE);
}
void display_note(int x, int y, char* text, int value, MLV_Font *font_note, MLV_Font *font_end){
    MLV_draw_text_with_font(x, y, text, font_end, MLV_COLOR_WHITE);
    //select color
    MLV_Color color;

    char* note;

    if(value < 0){
        note = "F";
        color = MLV_COLOR_DARK_RED;
    }else if(value < 10){
        note = "E";
        color = MLV_COLOR_RED;
    }else if(value < 30){
        note = "D";
        color = MLV_COLOR_ORANGE;
    }else if(value < 50){
        note = "C";
        color = MLV_COLOR_YELLOW;
    }else if(value < 80){
        note = "B";
        color = MLV_COLOR_GREEN;
    }else{
        note = "A";
        color = MLV_COLOR_GOLD;
    }

    //draw background circle
    MLV_draw_filled_circle(x + 385, y + 30, 30, color);
    MLV_draw_text_with_font(x + 370, y, note, font_note, MLV_COLOR_WHITE);
}
void init_end(int *win, MLV_Font *font_end, MLV_Font *font_hud, MLV_Font *font_note,int width, Stats *stats, Player *player, double *music_volume)
{

    struct timespec last, new;
    double accum;
    int leave = 0;
    stats->time = (MLV_get_time() - stats->start_time) / 1000;
    stats->nb_life = player->life;
    stats->nb_bonus = player->nuke + player->shield + player->shot;
    stats->nb_shoot = player->shot;
    int mouse_x, mouse_y;
    MLV_Image *background = MLV_load_image("./img/sea_.png");
    MLV_Image *cloud = MLV_load_image("./img/cloud.png");
    MLV_resize_image(cloud, WIDTH, HEIGHT);
    MLV_resize_image(background, WIDTH, HEIGHT);
    MLV_Music *music;
    if (*win)
    {
        music = MLV_load_music("sound/victory_music.mp3");
    }
    else
    {
        music = MLV_load_music("sound/loose_music.mp3");
    }

    MLV_play_music(music, *music_volume, -1);
    int x = 0;
    int y = HEIGHT;
    int y2 = HEIGHT;
    int note;
    //int ratio =((stats->nb_shoot)/2 / stats->nb_enemy_killed)*100;
    //calcul du ratio
   
    printf("nb shoot %d\n", stats->nb_shoot);
    printf("nb enemy killed %d\n", stats->nb_enemy_killed);
    while (!leave)
    {
        clock_gettime(CLOCK_REALTIME, &last);
        /* Display of the current frame */
        /* THIS FUNCTION CALL A SINGLE TIME MLV_actualize_window */
        // draw_window(&param, &grid);

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

        MLV_get_mouse_position(&mouse_x, &mouse_y);
        draw_button(290, 600, 220, 70, "LEAVE", font_hud, mouse_x, mouse_y);
        MLV_draw_filled_rectangle(WIDTH / 2 - 500 / 2, 260, 500, 300, MLV_COLOR_NAVY_BLUE);
        MLV_draw_rectangle(WIDTH / 2 - 500 / 2, 260, 500, 300, MLV_COLOR_WHITE);

        display_info(180, 280, "Life remaining", stats->nb_life, font_hud);
        display_info(180, 320, "Bonus remaining", stats->nb_bonus, font_hud);
        display_info(180, 360, "Enemy killed", stats->nb_enemy_killed, font_hud);
        display_info(180, 400, "Time in seconde", stats->time, font_hud);
        note = stats->nb_life + stats->nb_bonus + stats->nb_enemy_killed - stats->time/2;
        display_note(180, 490, "Rank", note, font_note, font_hud);
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
            mouse_x >= 290 && mouse_x <= 290 + 220 &&
            mouse_y >= 600 && mouse_y <= 600 + 70)
        {
            leave = 1;
        }
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
    MLV_stop_music();
    MLV_free_music(music);
    MLV_free_image(background);
    MLV_free_image(cloud);
}