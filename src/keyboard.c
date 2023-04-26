#include <MLV/MLV_all.h>
#include "../include/const.h"
#include "../include/struct.h"
#include "../include/missile.h"
#include "../include/enemy.h"
#include "../include/collision.h"
#include "../include/nuke.h"

void check_keyboard_pressed(MLV_Event event, MLV_Keyboard_button key_sym, MLV_Button_state state, int *nb_missile, Player *player, Enemy **enemies, int * nb_enemy, Missile **missiles,Nuke * nuke_obj, MLV_Sound *rocket, MLV_Sound *hit,double *effect_volume)
{
  if (event == MLV_KEY && key_sym == MLV_KEYBOARD_SPACE && state == MLV_PRESSED)
  {
    if (*nb_missile < 4)
    {
      init_missile(missiles, nb_missile, player->x + 10, player->y + 10, 0);
      init_missile(missiles, nb_missile, player->x + (player->width - 20), player->y + 10, 0);
      MLV_play_sound(rocket, *effect_volume);
    }
  }
  if (event == MLV_KEY && key_sym == MLV_KEYBOARD_b && state == MLV_PRESSED)
  {
    if (*nb_missile < 4 && player->shot > 0)
    {
      init_missile(missiles, nb_missile, player->x + 30, player->y + 10, 1);
      player->shot--;
      MLV_play_sound(rocket, *effect_volume);
    }
  }
  if (event == MLV_KEY && key_sym == MLV_KEYBOARD_n && state == MLV_PRESSED && player->nuke > 0 && nuke_obj->state == 0)
  {

    // check_collision_nuke_enemy(&nuke_obj, &enemies, &nb_enemy, &hit, effect_volume);
    player->nuke--;
    nuke_obj->is_use = 1;
    nuke_obj->fire = 1;

    // MLV_play_sound(rocket, *effect_volume);
  }
  if (nuke_obj->is_use == 1)
    {
      
      update_nuke(nuke_obj);
      
      if (event == MLV_KEY && key_sym == MLV_KEYBOARD_n && state == MLV_PRESSED && nuke_obj->state == 1)
      {
        
        
       
        nuke_obj->anim_state = 99;
        nuke_obj->fire =0;
        nuke_obj->state =0;
        nuke_obj->is_use =0;
      }
      if(nuke_obj->state == 0 && nuke_obj->fire == 1)nuke_obj->state = 1;
    }
}