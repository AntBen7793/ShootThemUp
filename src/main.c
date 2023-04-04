#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../include/struct.h"

#include "../include/missile.h"
#include "../include/player.h"
#include "../include/const.h"
#include "../include/enemy.h"
#include "../include/collision.h"
#include "../include/level.h"

int main(int argc, char* argv[]) {
  printf("Le début de quelque chose de grand\n");
  MLV_create_window("Projet", "", WIDTH, HEIGHT);
  int quit = 0;
  struct timespec last, new;
  MLV_Event event;
  MLV_Keyboard_button key_sym;  
  MLV_Button_state state;
  double accum;
  int x = 0;
  int y = 800;
  int y2 = 800;
  char** waves = NULL;
  int nb_wave =0;
  int current_wave =0;
  MLV_Image * background;
  MLV_Image * cloud;
  background = MLV_load_image("./img/sea_.png");
  cloud = MLV_load_image("./img/cloud.png");
  MLV_resize_image(cloud, WIDTH, HEIGHT);
  MLV_resize_image(background, WIDTH, HEIGHT);
  Player player = init_player();


  /* Music */
  MLV_init_audio();
  //MLV_Sound* rocket =  MLV_load_sound("soud/rocket.mp3");
  MLV_Music * music = MLV_load_music("sound/music.mp3");
  MLV_play_music(music, 1.0, -1);
  MLV_Sound * explosion =  MLV_load_sound("sound/explosion.ogg");
  MLV_Sound * rocket =  MLV_load_sound("sound/rocket.ogg");
  int nb_missile = 0;
  Missile* missiles = NULL;

  int nb_enemy = 0;
  Enemy* enemies = NULL;

  //init_enemy(&enemies, &nb_enemy, 200, 10);
  init_level(&waves, &nb_wave, &current_wave);

MLV_Image** explosion_images = malloc(6 * sizeof(MLV_Image*));
for (int i = 0; i < 6; i++) {
    char filename[50];
    sprintf(filename, "./img/explosion_state%d.png", i);
    explosion_images[i] = MLV_load_image(filename);
}

  while (!quit) {
    /* Get the time in nanoseconds at the frame beginning */
    clock_gettime(CLOCK_REALTIME, &last);
    /* Display of the current frame */
    /* THIS FUNCTION CALL A SINGLE TIME MLV_actualize_window */
    //draw_window(&param, &grid);
    MLV_clear_window(MLV_COLOR_SKY_BLUE);
    y=y+3;
    y2=y2+1;
    if(y >= HEIGHT){
        y = 0;   
    }
    if(y2 >= HEIGHT){
        y2 = 0;   
    }
    update_player(&player);
    if(nb_enemy == 0){
    update_level(&waves, &nb_wave, &current_wave, &enemies, &nb_enemy);
    }
    //check_collision(player.x, player.y, player.width, player.width, enemy1.x, enemy1.y, enemy1.width, enemy1.width);
    if(event == MLV_KEY && key_sym == MLV_KEYBOARD_SPACE && state == MLV_PRESSED){
    if(nb_missile < 4){
     init_missile(&missiles, &nb_missile, player.x+10, player.y+10);
     init_missile(&missiles, &nb_missile, player.x+ (player.width - 20), player.y+10);
     MLV_play_sound(rocket,100);

     }
    }
    
    MLV_draw_image(background, x, y);
    MLV_draw_image(background, x, y-HEIGHT);
    MLV_draw_image(cloud, x, y2);
    MLV_draw_image(cloud, x, y2-HEIGHT);
    draw_player(&player);
    
    update_missile(&missiles, nb_missile);
    update_enemy(&enemies, &nb_enemy, explosion_images, &explosion);
    check_collision_enemy_missile(&enemies, &missiles, &nb_missile, &nb_enemy);
    //draw_missiles(&missiles, nb_missile);
    //draw_enemies(&enemies, nb_enemy);
    //MLV_draw_rectangle(enemy1.x, enemy1.y, enemy1.width, enemy1.width, MLV_COLOR_RED);
    //printf("%d\n", nb_missile);
    

    /* We get there at most one keyboard event each frame */
    event = MLV_get_event(&key_sym, NULL, NULL, NULL, NULL,
                          NULL, NULL, NULL, &state);
    
    
    /* Event resolution here... */
    /* Moves of the entities on the board */
    /* Collision resolutions */

    /* Get the time in nanoseconds at the frame ending */
    clock_gettime(CLOCK_REALTIME, &new);

    /* We compute here the time spent for the current frame */
    accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / 1000000000);

    /* We force here to wait if the frame was too short */
    if (accum < (1.0 / 48.0)) {
        MLV_wait_milliseconds((int)(((1.0 / 40.0) - accum) * 1000));
    }
    
    MLV_actualise_window();
  }
  for(int i = 0; i < nb_wave; i++){
    free(waves[i]);
  }
  free(waves);
  MLV_free_image(background);
  MLV_free_image(cloud);
  free(missiles);
  MLV_free_sound(explosion);
  MLV_free_sound(rocket);
  MLV_stop_music();
  MLV_free_music(music);

  MLV_free_window();
  printf("fin\n");
  return 0;
}