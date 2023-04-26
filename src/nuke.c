#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/bonus.h"

Nuke init_nuke(int x, int y)
{
    Nuke nuke;
    nuke.x = x;
    nuke.y = y;
    nuke.dmg = 100;
    nuke.width = WIDTH;
    nuke.height = 20;
    nuke.is_use = 0;
    nuke.state =0;
    nuke.fire =0;
    nuke.anim_state=0;
    nuke.sprite = MLV_load_image("./img/laser_emettor.png");
    nuke.nuke_laser = MLV_load_image("./img/laser.png");
    MLV_resize_image(nuke.sprite, 90, 90);
    return nuke;
}
void check_keyboard_nuke(Nuke* nuke){
    if(MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED){
        nuke->y -= 5;
    }

    if(MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED){
         nuke->y += 5;
    }    
}

void nuke_animation(Nuke * nuke){
        
        nuke->anim_state += 50;
        nuke->width = nuke->anim_state;
        
        //MLV_draw_rectangle(nuke->x, nuke->y, nuke->anim_state, nuke->height, MLV_COLOR_RED);
        MLV_resize_image(nuke->nuke_laser, nuke->width, nuke->height);
        MLV_draw_image(nuke->nuke_laser, nuke->x, nuke->y);
        MLV_draw_image(nuke->sprite, nuke->x, nuke->y-(nuke->height*2)+5);
        
}
void draw_nuke(Nuke* nuke){

    MLV_draw_rectangle(nuke->x, nuke->y, nuke->width, nuke->height, MLV_COLOR_RED);
    MLV_draw_image(nuke->sprite, nuke->x, nuke->y-(nuke->height*2)+5);
}

void update_nuke(Nuke* nuke){


    check_keyboard_nuke(nuke);
    draw_nuke(nuke);
}


