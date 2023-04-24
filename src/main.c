#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/party.h"
#include "../include/menu.h"
#include "../include/const.h"

int main(int argc, char* argv[]) {
  double music_volume = 0.5;
  double effect_volume = 0.5;
  double new_music_volume = 0.5;
  MLV_init_audio();
  MLV_Music *music = MLV_load_music("sound/music.mp3");
  MLV_create_window("Projet", "", WIDTH, HEIGHT);
  
  MLV_play_music(music, music_volume, -1);
  init_menu(&music_volume, &effect_volume, &new_music_volume, music);
  MLV_free_window();
  return 0;
}