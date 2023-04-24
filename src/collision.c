/**
 * @file collision.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../include/const.h"
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/missile.h"
#include "../include/missile_enemy.h"
#include "../include/enemy.h"
#include "../include/player.h"
#include "../include/bonus.h"

/**
 * @brief check_collision
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @param x2
 * @param y2
 * @param width2
 * @param height2
 * @return int
 */
int check_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2)
{
    if (x < x2 + width2 &&
        x + width > x2 &&
        y < y2 + height2 &&
        height + y > y2)
    {
        return 1;
    }
    return 0;
}

void check_collision_enemy_missile(Enemy **enemies, Missile **missiles, int *nb_missile, int *nb_enemy, MLV_Sound **sound, double *effect_volume)
{

    for (int i = 0; i < *nb_missile; i++)
    {
        if (check_missile_collision_border(&((*missiles)[i])) == 1)
        {
            remove_missile(missiles, i, nb_missile);
            break;
        }
        for (int j = 0; j < *nb_enemy; j++)
        {
            if (check_collision((*missiles)[i].x, (*missiles)[i].y, (*missiles)[i].width, (*missiles)[i].height, (*enemies)[j].x, (*enemies)[j].y, (*enemies)[j].width, (*enemies)[j].width) == 1)
            {

                MLV_play_sound((*sound), *effect_volume);
                (*enemies)[j].life = (*enemies)[j].life - (*missiles)[i].dmg;
                // remove_enemy(enemies, j, nb_enemy);
                if ((*missiles)[i].type != 1)
                {
                    remove_missile(missiles, i, nb_missile);
                }

                // printf("life => %d\n", (*enemies)[j].life);

                break;
            }
        }
    }
}
void check_collision_enemy_missile_player(Player *player, Missile_enemy **missiles_enemy, int *nb_missile_enemy, int *quit, MLV_Sound **sound, double *effect_volume)
{

    for (int i = 0; i < *nb_missile_enemy; i++)
    {
        if (check_missile_enemy_collision_border(&((*missiles_enemy)[i])) == 1)
        {
            remove_missile_enemy(missiles_enemy, i, nb_missile_enemy);
            break;
        }
        if (check_collision((*missiles_enemy)[i].x, (*missiles_enemy)[i].y, (*missiles_enemy)[i].width, (*missiles_enemy)[i].height, (*player).x, (*player).y, (*player).width, (*player).width) == 1)
        {
            MLV_play_sound((*sound), *effect_volume);
            if (player->shield > 0)
            {
                (*player).shield = (*player).shield - 1;
            }
            else
            {
                (*player).life = (*player).life - (*missiles_enemy)[i].dmg;
            }
            if ((*player).life < 0)
                (*player).life = 0;
            remove_missile_enemy(missiles_enemy, i, nb_missile_enemy);
        }
    }
    if ((*player).life <= 0)
    {
        printf("GAME OVER");
        //(*player).life = 100;
        (*quit) = 1;
    }
}

void check_collision_bonus_player(Player *player, Bonus **bonus_list, int *nb_bonus, MLV_Sound **sound, double *effect_volume)
{

    for (int i = 0; i < *nb_bonus; i++)
    {
        if (check_bonus_collision_border(&((*bonus_list)[i])) == 1)
        {
            remove_bonus(bonus_list, i, nb_bonus);
            break;
        }
        if (check_collision((*bonus_list)[i].x, (*bonus_list)[i].y, (*bonus_list)[i].width, (*bonus_list)[i].width, (*player).x, (*player).y, (*player).width, (*player).width) == 1)
        {
            MLV_play_sound((*sound), *effect_volume);
            use_bonus(&(*bonus_list)[i], player);
            remove_bonus(bonus_list, i, nb_bonus);
        }
    }
}

void check_collision_enemy(Player *player, Enemy **enemies, int *nb_enemy, int *quit, MLV_Sound **sound, double *effect_volume)
{

    for (int i = 0; i < *nb_enemy; i++)
    {
        if (check_enemy_collision_border(&((*enemies)[i])) == 1)
        {
            remove_enemy(enemies, i, nb_enemy);
            player->life -= 34;
            break;
        }
    }
    if ((*player).life <= 0)
    {
        printf("GAME OVER");
        //(*player).life = 100;
        (*quit) = 1;
    }
}

void check_collision_nuke_enemy(Nuke* nuke,Enemy **enemies, int *nb_enemy, MLV_Sound **sound, double *effect_volume)
{

    for (int i = 0; i < *nb_enemy; i++)
    {
        if (check_collision((*enemies)[i].x, (*enemies)[i].y, (*enemies)[i].width, (*enemies)[i].width, (*nuke).x, (*nuke).y, (*nuke).width, (*nuke).height) == 1)
        {
           (*enemies)[i].life = (*enemies)[i].life - (*nuke).dmg;
           
        }
    }
}
