#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../include/player.h"
#include "../include/const.h"
#include "../include/enemy.h"
#include "../include/collision.h"

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
  MLV_Image * background;
  background = MLV_load_image("./img/sea_.png");
  MLV_resize_image(background, WIDTH, HEIGHT);
  Player player = init_player();
  Enemy enemy1 = init_enemy(400);
  while (!quit) {
    /* Get the time in nanoseconds at the frame beginning */
    clock_gettime(CLOCK_REALTIME, &last);
    /* Display of the current frame */
    /* THIS FUNCTION CALL A SINGLE TIME MLV_actualize_window */
    //draw_window(&param, &grid);
    MLV_clear_window(MLV_COLOR_SKY_BLUE);
    y= y+2;

    if(y >= HEIGHT ){
        y = 0;   
    }

    update_player(&player);
    update_enemy(&enemy1);
    check_collision(player.x, player.y, player.width, player.width, enemy1.x, enemy1.y, enemy1.width, enemy1.width);
    MLV_draw_image(background, x, y);
    MLV_draw_image(background, x, y-HEIGHT);

    draw_player(&player);
    MLV_draw_rectangle(enemy1.x, enemy1.y, enemy1.width, enemy1.width, MLV_COLOR_RED);


    /* We get there at most one keyboard event each frame */
    event = MLV_get_event(&key_sym, NULL, NULL, NULL, NULL,
                          NULL, NULL, NULL, &state);
    if(event == MLV_KEY && key_sym == MLV_KEYBOARD_z){
     

    }
    
    /* Event resolution here... */
    /* Moves of the entities on the board */
    /* Collision resolutions */

    /* Get the time in nanoseconds at the frame ending */
    clock_gettime(CLOCK_REALTIME, &new);

    /* We compute here the time spent for the current frame */
    accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / 1000000000);

    /* We force here to wait if the frame was too short */
    if (accum < (1.0 / 48.0)) {
        MLV_wait_milliseconds((int)(((1.0 / 100.0) - accum) * 1000));
    }
    
    MLV_actualise_window();
  }
  MLV_free_image(background);

  
  MLV_free_window();
  printf("fin\n");
  return 0;
}