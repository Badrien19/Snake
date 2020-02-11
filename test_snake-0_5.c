/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_snake-0_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:48:01 by badrien           #+#    #+#             */
/*   Updated: 2020/02/11 11:29:10 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../libft/libft.h"

/*
** 
** lst add last
** mv lst (move x or y)
** aff lst
*/

typedef struct s_food
{
    int x;
    int y;
    int alive;
}             t_food;

typedef struct s_snake_part
{
    int x;
    int y;
    int color;
    t_snake_part *next;
}               t_snake_part;

typedef struct s_snake
{
    int x;
    int y;
    int color;
    int direction;
    int score;
    int vitesse;
    t_snake_part *next;
}               t_snake;

typedef struct s_mlx
{
    void *mlx;
    void *window;
    int go;
    t_snake snake;
    t_food food;
}               t_mlx;

t_snake_part	*ft_lstlast(t_snake_part *snake_part)
{
	if (snake_part != NULL)
	{
		while (snake_part->next != '\0')
			snake_part = snake_part->next;
		return (lst);
	}
	return (0);
}


int new_snake_part(t_mlx *mlx)
{
   t_snake_part *next;

    printf("malloc\n");
   next = malloc(sizeof(t_snake_part));

   next->next= NULL;
   next->x = ft_lstlast(mlx->snake.next)->x;
   next->y = ft_lstlast(mlx->snake.next)->y;

    printf("new part position = %d - %d\n", next->x, next->y);


   return(0);
}

void aff_part(t_mlx *mlx, t_snake_part part)
{
    int i;
    int y;

    i = -4;
    y = -4;
    while(i < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, part.x + i, part.y + y, part.color);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, part.x + i, part.y + y, part.color);
            y++;      
       }
    y = -4;
    i++;
    }
}

void aff_snake(t_mlx *mlx)
{
    int i;
    int y;
    t_snake_part *part;

    i = -4;
    y = -4;
    while(i < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + i, mlx->snake.y + y, mlx->snake.color);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + i, mlx->snake.y + y, mlx->snake.color);
            y++;      
       }
    y = -4;
    i++;
    }

    part = mlx->snake.next;
    while(part)
    {
        printf("affichage part\n");
        aff_part(mlx, part);
        part = part->next;
    }
}

void aff_food(t_mlx *mlx)
{
    int i;
    int y;

    i = -4;
    y = -4;
    while(i < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, 0x00FF00);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, 0x00FF00);
            y++;      
       }
    y = -4;
    i++;
    }
}

void aff_bordure(t_mlx *mlx)
{
    int x = 50;
    int y = 50;
    mlx_string_put(mlx->mlx, mlx->window, 50, 40, 0x00FF00, "Snake 0.1 :");

    mlx_string_put(mlx->mlx, mlx->window, 150, 40, 0x00FF00, "Score = ");
    mlx_string_put(mlx->mlx, mlx->window, 200, 40, 0x00FF00, ft_itoa(mlx->snake.score));

    if(mlx->go == 0)
        mlx_string_put(mlx->mlx, mlx->window, 120, 180, 0x00FF00, "Press \"Enter\" to begin! ");

    while(x < 350)
        mlx_pixel_put(mlx->mlx, mlx->window, x++, y, 0xFFFFFF);
    y = 350;
    x = 50;
    while(x < 350)
        mlx_pixel_put(mlx->mlx, mlx->window, x++, y, 0xFFFFFF);
    x = 50;
    y = 50;
    while(y < 350)
        mlx_pixel_put(mlx->mlx, mlx->window, x, y++, 0xFFFFFF);
    x = 350;
    y = 50;
    while(y < 350)
        mlx_pixel_put(mlx->mlx, mlx->window, x, y++, 0xFFFFFF);
}

void food(t_mlx *mlx)
{
    if(mlx->food.alive == 1)
        return;
    srand(time(NULL));
    mlx->food.x= (rand() % (341 - 59 + 1)) + 59; // (rand() % (max - min + 1)) + min;
    mlx->food.y= (rand() % (341 - 59 + 1)) + 59;
    mlx->food.alive = 1;
}

void veriff(t_mlx *mlx)
{
    // Verification bordure
    if(mlx->snake.x > (350 - 5) || mlx->snake.x < (50 + 5) 
    || mlx->snake.y > (350 - 5) || mlx->snake.y < (50 + 5))
    {
        mlx->snake.direction = 5;
        mlx_string_put(mlx->mlx, mlx->window, 170, 150, 0xFF0000, "GAME OVER");
    }
    // Verification food
    if((mlx->snake.x >= mlx->food.x - 8 && mlx->snake.x <= mlx->food.x + 8) && (mlx->snake.y >= mlx->food.y - 8 && mlx->snake.y <= mlx->food.y + 8))
    {
        mlx->snake.score += 1;
        mlx->food.alive = 0;
        printf("Tentative creation part\n");
        ft_lstlast(mlx->snake.next) = new_snake_part(mlx);
    }
}
void reload(t_mlx *mlx)
{
    mlx_clear_window(mlx->mlx, mlx->window);
    aff_snake(mlx);
    aff_food(mlx);
    aff_bordure(mlx);
    veriff(mlx);
    food(mlx);
}

int swap_direction(int keycode, t_mlx *mlx)
{
    if(keycode == 36)
        mlx->go = 1;
    if(keycode == 53)
        mlx->snake.direction = 5;
    if (keycode == 126) // haut
        mlx->snake.direction = 1;
    if (keycode == 125) // bas
        mlx->snake.direction = 2;
    if (keycode == 123) // gauche
        mlx->snake.direction = 3;
    if (keycode == 124) // droite
        mlx->snake.direction = 4;
    return(0);
}

int superloop(t_mlx *mlx)
{
    usleep(mlx->snake.vitesse);

    if(mlx->go == 0)
        return (0);
    if(mlx->snake.direction == 4)
       mlx->snake.x += 3;
    if(mlx->snake.direction == 3)
        mlx->snake.x -= 3;
    if(mlx->snake.direction == 2)
        mlx->snake.y += 3;
    if(mlx->snake.direction == 1)
        mlx->snake.y -= 3;
    if(mlx->snake.direction == 5)
    {
        sleep(2);
        free(mlx);
        mlx_destroy_window(mlx->mlx, mlx->window);
        exit (-1);
    }
    reload(mlx);
    return (0);
}

int main(void)
{
    t_mlx *mlx;

    mlx = (t_mlx *) malloc(sizeof(t_mlx));
    mlx->mlx = mlx_init();
    mlx->window = mlx_new_window(mlx->mlx, 400, 400, "Snake 0.2");
    mlx->go = 0;
    mlx->snake.x = 200;
    mlx->snake.y = 200;
    mlx->snake.color = 0xF8F4F8;
    mlx->snake.direction = 2;
    mlx->snake.score = 0;
    mlx->snake.vitesse = 100;
    mlx->snake.next = NULL;
    mlx->food.alive = 0;

    reload(mlx);
    mlx_hook(mlx->window, 2, 0, swap_direction, mlx); // 2 pour keypress
    mlx_hook(mlx->window, 3, 0, swap_direction, mlx); // 3 pour keyrelease
    mlx_loop_hook(mlx->mlx, superloop, mlx);
    mlx_loop(mlx->mlx);
    return (0);
}