
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

void draw_level_button(int x, int y, int w, int h, char *text, MLV_Font *font, int mouse_x, int mouse_y, int *level, int number, double *music_volume, double *effect_volume, MLV_Music *music,MLV_Music *victory, MLV_Sound *start, int *pressed, int *transition_state)
{
    int state = 0;
    if (number <= *level)
    {
        state = 1;
    }
    int text_width, text_height;
    MLV_get_size_of_text(text, &text_width, &text_height);

    MLV_Color text_color = MLV_COLOR_WHITE;

    if (
        mouse_x >= x && mouse_x <= x + w &&
        mouse_y >= y && mouse_y <= y + h &&
        state == 1)
    {
        text_color = MLV_COLOR_ORANGE1;
    }

    if (state == 0)
    {
        MLV_draw_text_box_with_font(x, y, w, h, text, font, 1, MLV_COLOR_DARK_RED, MLV_COLOR_GRAY, MLV_COLOR_BLUE4, MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_TEXT_CENTER);
    }
    else
    {
        MLV_draw_text_box_with_font(x, y, w, h, text, font, 1, MLV_COLOR_WHITE, text_color, MLV_COLOR_NAVY_BLUE, MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_TEXT_CENTER);
    }

    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
        mouse_x >= x && mouse_x <= x + w &&
        mouse_y >= y && mouse_y <= y + h &&
        number <= *level)
    {
        MLV_play_sound(start, *effect_volume);
        while (*transition_state < WIDTH)
        {

            /* Dessiner la transition */
            MLV_draw_filled_rectangle(0, 0, *transition_state, HEIGHT, MLV_COLOR_BLACK);

            /* Actualiser l'affichage */
            MLV_actualise_window();

            /* Temporisation pour contrôler la vitesse de la transition */
            MLV_wait_milliseconds(10);

            /* Mettre à jour l'état de la transition */
            *transition_state += 30;
        }
        MLV_stop_music();
        init_party(effect_volume, music_volume, number, level);
        if(*level >= 7){
            MLV_play_music(victory, *music_volume, -1);
        }else{
            MLV_play_music(music, *music_volume, -1);
        }
       
        *pressed = 1;
        *transition_state = 0;

    }

    // printf("level : %d\n", *level);
}
void draw_gauge(int x, int y, int w, int h, char *text, MLV_Font *font, MLV_Font *font_title, int mouse_x, int mouse_y, double *volume)
{
    // Dessiner la jauge
    MLV_draw_text_with_font(x, y - 30, text, font_title, MLV_COLOR_GRAY);
    MLV_draw_filled_rectangle(x, y, w, h, MLV_COLOR_NAVY_BLUE);
    MLV_draw_rectangle(x, y, w, h, MLV_COLOR_WHITE);

    // Calculer la position du curseur en fonction du volume actuel
    int cursor_x = x + (*volume) * w;

    // Dessiner le curseur
    MLV_draw_filled_rectangle(cursor_x - 5, y, 10, h, MLV_COLOR_WHITE);

    // Calculer la valeur du volume en pourcentage (de 0 à 100)
    int volume_percentage = (int)(*volume * 100);

    // Afficher la valeur du volume à droite de la jauge
    char volume_text[10];
    snprintf(volume_text, sizeof(volume_text), "%d", volume_percentage);
    MLV_draw_text_with_font(x + w + 10, y + 10, volume_text, font, MLV_COLOR_GRAY);

    // Vérifier si la souris est en train de cliquer sur la jauge
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
        mouse_x >= x && mouse_x <= x + w &&
        mouse_y >= y && mouse_y <= y + h)
    {
        // Mettre à jour la valeur du volume en fonction de la position de la souris
        *volume = (double)(mouse_x - x) / w;
    }
}

void init_menu(double *music_volume, double *effect_volume, double *new_music_volume, MLV_Music *music)
{
    int mouse_x, mouse_y;
    int button_width = 220;
    int button_height = 70;
    int button_x = WIDTH / 2 - button_width / 2;
    int button_y = 400;
    int button_y2 = 500;
    int button_y3 = 600;
    int margin = 20;
    int transition_state = 1;
    MLV_Font *font = MLV_load_font("./font/ARCADECLASSIC.ttf", 50);
    MLV_Font *font_title = MLV_load_font("./font/ARCADECLASSIC.ttf", 30);
    double accum;
    int quit = 0;
    struct timespec last, new;
    int y = 0;
    int y2 = 0;
    int x = 0;
    int main_menu_state = 1; // 1 pour afficher le menu principal, 0 pour le masquer
    int setting_menu_state = 0;
    int level_menu_state = 0;
    int pressed = 0;
    int level = 1;
    MLV_Image *background = MLV_load_image("./img/sea_.png");
    MLV_Image *cloud = MLV_load_image("./img/cloud.png");
    MLV_Image *logo = MLV_load_image("./img/topgun.png");
    MLV_Sound *start = MLV_load_sound("sound/game-start.wav");
    MLV_Sound *select = MLV_load_sound("sound/select.wav");
    MLV_Sound *cheat = MLV_load_sound("sound/bonus.ogg");
    MLV_Music *victory = MLV_load_music("sound/victory.mp3");
    MLV_resize_image(cloud, WIDTH, HEIGHT);
    MLV_resize_image(logo, 600, 200);
    MLV_resize_image(background, WIDTH, HEIGHT);
    while (!quit)
    {
        /* Get the time in nanoseconds at the frame beginning */
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
        MLV_draw_image(logo, 100, 100);

        if (*music_volume != *new_music_volume)
        {
            MLV_stop_music();
            MLV_play_music(music, *new_music_volume, -1);
            *music_volume = *new_music_volume;
        }

        MLV_get_mouse_position(&mouse_x, &mouse_y);

        if (main_menu_state && pressed == 0) // Vérifier si le menu principal est actif
        {
            draw_button(button_x, button_y, button_width, button_height, "Play", font, mouse_x, mouse_y);
            draw_button(button_x, button_y2, button_width, button_height, "Setting", font, mouse_x, mouse_y);
            draw_button(button_x, button_y3, button_width, button_height, "Leave", font, mouse_x, mouse_y);
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
                mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y && mouse_y <= button_y + button_height)
            {
                MLV_play_sound(select, *effect_volume);
                main_menu_state = 0;
                setting_menu_state = 0;
                level_menu_state = 1;
                pressed = 1;
                // MLV_wait_milliseconds(100);
            }
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
                mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y2 && mouse_y <= button_y2 + button_height)
            {
                MLV_play_sound(select, *effect_volume);
                main_menu_state = 0;
                setting_menu_state = 1;
                level_menu_state = 0;
                pressed = 1;
                // MLV_wait_milliseconds(100);
            }
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
                mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y3 && mouse_y <= button_y3 + button_height)
            {
                MLV_play_sound(select, *effect_volume);
                return;
            }
        }
        if (level_menu_state && pressed == 0) // Vérifier si le menu des level est actif
        {

            draw_level_button(button_x - button_width - margin, button_y, button_width, button_height, "Level 1", font, mouse_x, mouse_y, &level, 1, music_volume, effect_volume, music, victory,start, &pressed, &transition_state);
            draw_level_button(button_x, button_y, button_width, button_height, "Level 2", font, mouse_x, mouse_y, &level, 2, music_volume, effect_volume, music, victory,start, &pressed, &transition_state);
            draw_level_button(button_x + button_width + margin, button_y, button_width, button_height, "Level 3", font, mouse_x, mouse_y, &level, 3, music_volume, effect_volume, music,victory, start, &pressed, &transition_state);
            draw_level_button(button_x - button_width - margin, button_y2, button_width, button_height, "Level 4", font, mouse_x, mouse_y, &level, 4, music_volume, effect_volume, music,victory, start, &pressed, &transition_state);
            draw_level_button(button_x, button_y2, button_width, button_height, "Level 5", font, mouse_x, mouse_y, &level, 5, music_volume, effect_volume, music, victory,start, &pressed, &transition_state);
            draw_level_button(button_x + button_width + margin, button_y2, button_width, button_height, "Level 6", font, mouse_x, mouse_y, &level, 6, music_volume, effect_volume, music,victory, start, &pressed, &transition_state);

            draw_button(button_x, button_y3, button_width, button_height, "Back", font, mouse_x, mouse_y);

            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
                mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y3 && mouse_y <= button_y3 + button_height)
            {
                MLV_play_sound(select, *effect_volume);
                main_menu_state = 1;
                setting_menu_state = 0;
                level_menu_state = 0;
                pressed = 1;
            }

            if (MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED &&
                MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED &&
                MLV_get_keyboard_state(MLV_KEYBOARD_KP6) == MLV_PRESSED)
            {
                MLV_play_sound(cheat, *effect_volume);
                level = 6;
            }

            if (MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED &&
                MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED &&
                MLV_get_keyboard_state(MLV_KEYBOARD_KP1) == MLV_PRESSED)
            {
                 MLV_play_sound(cheat, *effect_volume);
                level = 1;
            }
        }

        if (setting_menu_state && pressed == 0) // Vérifier si le menu des paramètres est actif
        {

            draw_gauge(button_x, button_y, button_width, button_height, "Music Volume", font, font_title, mouse_x, mouse_y, new_music_volume);
            draw_gauge(button_x, button_y2, button_width, button_height, "Effect Volume", font, font_title, mouse_x, mouse_y, effect_volume);
            draw_button(button_x, button_y3, button_width, button_height, "Back", font, mouse_x, mouse_y);
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
                mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y3 && mouse_y <= button_y3 + button_height)
            {
                MLV_play_sound(select, *effect_volume);
                main_menu_state = 1;
                setting_menu_state = 0;
                level_menu_state = 0;
                pressed = 1;
                // MLV_wait_milliseconds(100);
            }
        }

        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED)
        {
            pressed = 0;
        }

        /* Get the time in nanoseconds at the frame ending */
        clock_gettime(CLOCK_REALTIME, &new);

        /* We compute here the time spent for the current frame */
        accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / 1000000000);

        /* We force here to wait if the frame was too short */
        if (accum < (1.0 / 48.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - accum) * 1000));
        }

        MLV_actualise_window();
    }
    MLV_free_image(cloud);
    MLV_free_image(background);
    MLV_stop_music();
    MLV_free_music(music);
    MLV_free_sound(start);
    MLV_free_sound(select);
    MLV_free_sound(cheat);

    MLV_free_font(font);
    MLV_free_font(font_title);
    

}