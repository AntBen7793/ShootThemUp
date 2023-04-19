#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/bonus.h"

void init_bonus(Bonus **bonus_list, int *nb_bonus, int x, int y, int type)
{
    Bonus bonus;
    bonus.x = x;
    bonus.y = y;
    bonus.type = type;
    bonus.width = 50;
    bonus.speed = 1;
    bonus.animation_state = 0;
    switch (type)
    {
    case 0:
        bonus.sprite = MLV_load_image("./img/shield_icon.png");       
        break;
    case 1:
        bonus.sprite = MLV_load_image("./img/heart_icon.png");
        break;
    case 2:
        bonus.sprite = MLV_load_image("./img/fireball_icon.png");
        break;
    
    default:
        break;
    }

    MLV_resize_image(bonus.sprite, bonus.width, bonus.width);
    add_bonus(bonus_list, bonus, nb_bonus);
}

void add_bonus(Bonus **bonus_list, Bonus bonus, int *nb_bonus)
{
    *bonus_list = (Bonus *)realloc(*bonus_list, (*nb_bonus + 1) * sizeof(Bonus));
    if (*bonus_list == NULL)
    {
        printf("Bonus add error...\n");
        return;
    }
    (*bonus_list)[*nb_bonus] = bonus;
    *nb_bonus = (*nb_bonus) + 1;
}
void draw_bonus(Bonus *bonus)
{

    MLV_draw_image((*bonus).sprite, (*bonus).x, (*bonus).y);
    MLV_draw_rectangle((*bonus).x, (*bonus).y, (*bonus).width, (*bonus).width, MLV_COLOR_RED);
}
void update_bonus(Bonus **bonus_list, int nb_bonus, MLV_Image **heart_animation, MLV_Image **shield_animation, MLV_Image **fireball_animation)
{
    for (int i = 0; i < nb_bonus; i++)
    {
        Bonus *bonus = &((*bonus_list)[i]);

        movement_bonus(bonus);
        draw_bonus(bonus);

        bonus->animation_state++;
        
        if (bonus->animation_state < 11 && bonus->animation_state > 4)
        {

            switch (bonus->type)
            {
            case 0:
                bonus->sprite = shield_animation[bonus->animation_state - 4];                  
                break;
            case 1:
                bonus->sprite = heart_animation[bonus->animation_state - 4];
               
                break;
            case 2:
                bonus->sprite = fireball_animation[bonus->animation_state - 4];
                break;
            
            default:
                break;
            }
            
           
            MLV_resize_image(bonus->sprite, bonus->width, bonus->width);
        }

        if (bonus->animation_state > 11){bonus->animation_state = 0;}
        
    }
}

void movement_bonus(Bonus *bonus)
{
    // printf("test => %d\n", enemy->type);
    switch (bonus->type)
    {
    case 0:
        bonus->y += bonus->speed;
        break;
    case 1:
        bonus->y += bonus->speed;
        break;
    case 2:
        bonus->y += bonus->speed;
        break;
    default:

        break;
    }
}

void remove_bonus(Bonus **bonus_list, int index, int *nb_bonus)
{

    if (index < 0 || index >= *nb_bonus)
    {
        printf("Index out of bounds error...\n");
        return;
    }

    for (int i = index; i < *nb_bonus - 1; i++)
    {
        (*bonus_list)[i] = (*bonus_list)[i + 1];
    }
    (*nb_bonus)--;

    Bonus *temp = (Bonus *)realloc(*bonus_list, *nb_bonus * sizeof(Bonus));
    if (temp == NULL && *nb_bonus > 0)
    {
        printf("Memory allocation error while removing missile.\n");
        return;
    }
    *bonus_list = temp;
}

int check_bonus_collision_border(Bonus *bonus)
{
    if (bonus->y >= HEIGHT)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
