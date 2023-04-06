#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/party.h"
#include "../include/menu.h"
#include "../include/const.h"

int main(int argc, char* argv[]) {
  MLV_create_window("Projet", "", WIDTH, HEIGHT);
  init_menu();
  MLV_free_window();
  return 0;
}