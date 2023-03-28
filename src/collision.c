#include "../include/const.h"
#include <stdio.h>


int check_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2){
    if(x < x2 + width2 &&
   x + width > x2 &&
   y < y2 + height2 &&
   height + y > y2){
        printf("ui\n");
        return 1;
    }
    return 0;
}
