#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../include/struct.h"
#include "../include/missile_enemy.h"
#include "../include/health_bar.h"
#include "../include/missile.h"
#include "../include/player.h"
#include "../include/const.h"
#include "../include/enemy.h"
#include "../include/collision.h"
#include "../include/level.h"
#include "../include/party.h"
#include "../include/bonus.h"
#include "../include/nuke.h"
#include "../include/keyboard.h"
#include "../include/menu.h"
#include "../include/end.h"

void init_party(double *effect_volume, double *music_volume, int level, int *current)
{
  printf("Le début de quelque chose de grand\n");

  int quit = 0;
  int finish = 0;
  struct timespec last, new;
  MLV_Event event;
  MLV_Keyboard_button key_sym;
  MLV_Button_state state;
  double accum;
  int x = 0;
  int y = HEIGHT;
  int y2 = HEIGHT;
  char **waves = NULL;
  int nb_wave = 0;
  int current_wave = 0;
  Stats stats;
  stats.nb_bonus = 0;
  stats.nb_enemy_killed = 0;
  stats.nb_life = 0;
  stats.nb_shoot = 0;
  stats.start_time = MLV_get_time();
  MLV_Image *background = MLV_load_image("./img/sea_.png");
  MLV_Image *cloud = MLV_load_image("./img/cloud.png");
  MLV_Image *hud = MLV_load_image("./img/hud.png");
  MLV_Image *shield = MLV_load_image("./img/shield_icon.png");
  MLV_Image *fireball = MLV_load_image("./img/fireball_icon.png");
  MLV_Image *nuke = MLV_load_image("./img/nuke_icon.png");
  MLV_Image *filtre = MLV_load_image("./img/filtre.png");
  MLV_Font *font_hud = MLV_load_font("./font/ARCADECLASSIC.ttf", 40);
  MLV_Font *font_end = MLV_load_font("./font/ARCADECLASSIC.ttf", 70);
  MLV_Font *font_note = MLV_load_font("./font/ARCADECLASSIC.ttf", 60);
  // MLV_Image *super_shot = MLV_load_image("./img/shield_icon.png");
  MLV_resize_image(shield, 60, 60);
  MLV_resize_image(fireball, 50, 50);
  MLV_resize_image(nuke, 50, 50);
  MLV_resize_image(filtre, 160, 60);
  MLV_resize_image(hud, 210, 100);

  MLV_resize_image(cloud, WIDTH, HEIGHT);
  MLV_resize_image(background, WIDTH, HEIGHT);
  Player player = init_player();

  /* Music */
  // MLV_Sound* rocket =  MLV_load_sound("soud/rocket.mp3");
  MLV_Music *music = MLV_load_music("sound/DangerZone.mp3");
  MLV_play_music(music, *music_volume, -1);
  MLV_Sound *hit = MLV_load_sound("sound/hit.wav");
  MLV_Sound *take = MLV_load_sound("sound/bonus.ogg");
  MLV_Sound *explosion = MLV_load_sound("sound/explosion.ogg");
  MLV_Sound *rocket = MLV_load_sound("sound/rocket.ogg");
  MLV_Sound *crash = MLV_load_sound("sound/crash.wav");
  int nb_missile = 0;
  Missile *missiles = NULL;
  int nb_missile_enemy = 0;
  Missile_enemy *missiles_enemy = NULL;
  int nb_enemy = 0;
  Enemy *enemies = NULL;
  int nb_bonus = 0;
  Bonus *bonus_list = NULL;
  int win = 0;
  Nuke nuke_obj = init_nuke(0, 100);
  // init_enemy(&enemies, &nb_enemy, 200, 10);
  init_level(&waves, &nb_wave, &current_wave, level);

  MLV_Image **explosion_images = malloc(9 * sizeof(MLV_Image *));
  for (int i = 0; i < 9; i++)
  {
    char filename[50];
    sprintf(filename, "./img/explosion1/plane_state%d.png", i);
    explosion_images[i] = MLV_load_image(filename);
  }

  MLV_Image **heart_animation = malloc(7 * sizeof(MLV_Image *));
  for (int i = 0; i < 7; i++)
  {
    char filename[50];
    sprintf(filename, "./img/animation/heart/heart_state%d.png", i);
    heart_animation[i] = MLV_load_image(filename);
  }

  MLV_Image **shield_animation = malloc(7 * sizeof(MLV_Image *));
  for (int i = 0; i < 7; i++)
  {
    char filename[50];
    sprintf(filename, "./img/animation/shield/shield_state%d.png", i);
    shield_animation[i] = MLV_load_image(filename);
  }

  MLV_Image **fireball_animation = malloc(7 * sizeof(MLV_Image *));
  for (int i = 0; i < 7; i++)
  {
    char filename[50];
    sprintf(filename, "./img/animation/fireball/fireball_state%d.png", i);
    fireball_animation[i] = MLV_load_image(filename);
  }

  while (!finish)
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

    /* We get there at most one keyboard event each frame */
    event = MLV_get_event(&key_sym, NULL, NULL, NULL, NULL,
                          NULL, NULL, NULL, &state);
    // printf("shield : %d\n", player.shield);
    /* Event resolution here... */
    /* Moves of the entities on the board */
    /* Collision resolutions */
    if (nb_enemy == 0)
    {
      update_level(&waves, &nb_wave, &current_wave, &enemies, &nb_enemy, &bonus_list, &nb_bonus, &quit, &win);
    }

    update_player(&player);
    MLV_draw_image(background, x, y);
    MLV_draw_image(background, x, y - HEIGHT);
    MLV_draw_image(cloud, x, y2);
    MLV_draw_image(cloud, x, y2 - HEIGHT);
    if (quit)
    {
      if (win == 0)
      {
        MLV_stop_music();
        MLV_play_sound(crash, *effect_volume);
        int transition_state = 0;
        int square_size = 10;
        int x = 0;
        int y = 0;
        int width = WIDTH;
        int height = HEIGHT;
        while (transition_state < WIDTH && transition_state < HEIGHT)
        {
          /* Dessiner les carrés noirs en spirale */
          for (int i = 0; i < width; i += square_size)
          {
            MLV_draw_filled_rectangle(x + i, y, square_size, square_size, MLV_COLOR_BLACK);
          }
          for (int i = square_size; i < height; i += square_size)
          {
            MLV_draw_filled_rectangle(x + width - square_size, y + i, square_size, square_size, MLV_COLOR_BLACK);
          }
          for (int i = width - square_size * 2; i >= 0; i -= square_size)
          {
            MLV_draw_filled_rectangle(x + i, y + height - square_size, square_size, square_size, MLV_COLOR_BLACK);
          }
          for (int i = height - square_size * 2; i >= square_size; i -= square_size)
          {
            MLV_draw_filled_rectangle(x, y + i, square_size, square_size, MLV_COLOR_BLACK);
          }

          /* Actualiser l'affichage */
        
          MLV_actualise_window();

          /* Temporisation pour contrôler la vitesse de la transition */
          MLV_wait_milliseconds(20);

          /* Mettre à jour les variables pour la prochaine itération */
          x += square_size;
          y += square_size;
          width -= square_size * 2;
          height -= square_size * 2;
          transition_state += square_size * 2;
        }

        transition_state = 0;
      }

      init_end(&win, font_end, font_hud, font_note, 300, &stats, &player, music_volume, effect_volume);
      finish = 1;

      if (win == 1 && level >= *current)
      {
        *current += 1;
        win = 0;
      }
    }
    else
    {
      draw_player(&player);
      update_bonus(&bonus_list, nb_bonus, heart_animation, shield_animation, fireball_animation);
      update_missile_enemy(&missiles_enemy, nb_missile_enemy);
      update_missile(&missiles, nb_missile);
      update_enemy(&enemies, &nb_enemy, explosion_images, &explosion, &missiles_enemy, &stats, &nb_missile_enemy, effect_volume);
      check_collision_enemy(&player, &enemies, &nb_enemy, &quit, &hit, effect_volume);
      check_collision_enemy_missile(&enemies, &missiles, &nb_missile, &nb_enemy, &hit, effect_volume);
      check_collision_enemy_missile_player(&player, &missiles_enemy, &nb_missile_enemy, &quit, &hit, effect_volume);
      check_collision_bonus_player(&player, &bonus_list, &nb_bonus, &take, effect_volume);
      check_keyboard_pressed(event, key_sym, state, &nb_missile, &player, &enemies, &nb_enemy, &missiles, &nuke_obj, rocket, hit, effect_volume);

      if (nuke_obj.anim_state < 750 && nuke_obj.anim_state > 0)
      {

        nuke_animation(&nuke_obj);

        check_collision_nuke_enemy(&nuke_obj, &enemies, &nb_enemy, hit, effect_volume);
      }
      else
      {
        nuke_obj.anim_state = 750;
      }
      draw_health_bar(WIDTH - 200, HEIGHT - 100, 200, 20, &player, hud, shield, fireball, nuke, font_hud, filtre);
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
  for (int i = 0; i < nb_wave; i++)
  {
    free(waves[i]);
  }
  free(waves);
  free_animation_images(explosion_images, 7);
  free_animation_images(heart_animation, 7);
  free_animation_images(shield_animation, 7);
  free_animation_images(fireball_animation, 7);
  MLV_free_image(background);
  MLV_free_image(cloud);
  MLV_free_image(hud);
  MLV_free_image(nuke);
  MLV_free_image(shield);
  MLV_free_image(filtre);
  free(missiles);
  free(missiles_enemy);
  MLV_free_sound(explosion);
  MLV_free_sound(rocket);
  MLV_free_sound(hit);
  MLV_free_music(music);

  printf("fin\n");
}

void free_animation_images(MLV_Image **images, int nb)
{
  for (int i = 0; i < nb; i++)
  {
    MLV_free_image(images[i]); // Libère l'image chargée avec MLV_load_image
  }
  free(images); // Libère le tableau d'images alloué avec malloc
}