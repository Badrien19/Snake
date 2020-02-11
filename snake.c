/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:48:01 by badrien           #+#    #+#             */
/*   Updated: 2020/02/11 17:57:29 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../libft/libft.h"

typedef struct s_food
{
    int x;
    int y;
    int alive;
}             t_food;

typedef struct s_body
{
    int first;
    int x;
    int *prev_x;
    int y;
    int *prev_y;
    struct s_body *next;
}               t_body;

typedef struct s_snake
{
    int x;
    int y;
    int color;
    int direction;
    int score;
    int vitesse;

    t_body *body;

}               t_snake;

typedef struct s_mlx
{
    void *mlx;
    void *window;
    int go;
    t_snake snake;
    t_food food;
}               t_mlx;

t_body	*ft_bodylast(t_body *body)
{
	if (body != NULL)
	{
		while (body->next != '\0')
			body = body->next;
		return (body);
	}
	return (0);
}


void aff_snake(t_mlx *mlx)
{
    int i;
    int y;

    t_body *body;
    body = mlx->snake.body;

    while(body->next != NULL)
    {
        i = -3;
        y = -3;
        while(i < 4)
        {
            mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, 0x9FE855);
            while(y < 4)
            {
                mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, 0x9FE855);
                y++;      
            }
        y = -3;
        i++;

        }
    body = body->next;
    }
    
    i = -2;
    y = -2;
    while(i < 3)
    {
        mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, 0xFFD700);
        while(y < 3)
        {
            mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, 0xFFD700);
            y++;      
        }
    y = -2;
    i++;
    }
    
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

}

void aff_food(t_mlx *mlx)
{
    int i;
    int y;

    i = -4;
    y = -4;
    while(i < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, 0xB22222);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, 0xB22222);
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

t_body *add_body(int *x, int *y)
{
    t_body *body;
    
    body = malloc(sizeof(t_body));
    body->first = 0;
    body->next = NULL;
    body->prev_x = x;
    body->x = *x;
    body->prev_y = y;
    body->y = *y;

    return (body);
}
void veriff(t_mlx *mlx)
{
    t_body *next;
    
    next = mlx->snake.body;
    while(next != NULL)
    {
        if((mlx->snake.x >= next->x - 1 && mlx->snake.x <= next->x + 1) && (mlx->snake.y >= next->y - 1 && mlx->snake.y <= next->y + 1))
        {
        mlx->snake.direction = 5;
        mlx_string_put(mlx->mlx, mlx->window, 170, 150, 0xFF0000, "GAME OVER");
        }
    next = next->next;
    }

    next = ft_bodylast(mlx->snake.body);

    if(mlx->snake.x > (350 - 5) || mlx->snake.x < (50 + 5) 
    || mlx->snake.y > (350 - 5) || mlx->snake.y < (50 + 5))
    {
        mlx->snake.direction = 5;
        mlx_string_put(mlx->mlx, mlx->window, 170, 150, 0xFF0000, "GAME OVER");
    }
    
    if((mlx->snake.x >= mlx->food.x - 8 && mlx->snake.x <= mlx->food.x + 8) && (mlx->snake.y >= mlx->food.y - 8 && mlx->snake.y <= mlx->food.y + 8))
    {
        mlx->snake.score += 1;
        mlx->food.alive = 0;
        next->next = add_body(&(next->x), &(next->y));
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
    if (keycode == 126 && mlx->snake.direction != 2) // haut
        mlx->snake.direction = 1;
    if (keycode == 125 && mlx->snake.direction != 1) // bas
        mlx->snake.direction = 2;
    if (keycode == 123 && mlx->snake.direction != 4) // gauche
        mlx->snake.direction = 3;
    if (keycode == 124 && mlx->snake.direction != 3) // droite
        mlx->snake.direction = 4;
    return(0);
}

int inc_tail(t_mlx *mlx ,t_body *body, int x, int y)
{
    if(body == NULL)
        return (0);

    inc_tail(mlx , body->next, body->x, body->y);
    if(body->first < 3)
        body->first += 1;
    else
    {
        body->x = x;
        body->y = y;
        body->first = 0;
    }
    return (0);
}

int superloop(t_mlx *mlx)
{
    usleep(mlx->snake.vitesse);

   inc_tail(mlx, mlx->snake.body, mlx->snake.x, mlx->snake.y);

    mlx->snake.body->x = mlx->snake.x;
    mlx->snake.body->y = mlx->snake.y;
    
    if(mlx->go == 0)
        return (0);
    if(mlx->snake.direction == 4)
       mlx->snake.x += 2;
    if(mlx->snake.direction == 3)
        mlx->snake.x -= 2;
    if(mlx->snake.direction == 2)
        mlx->snake.y += 2;
    if(mlx->snake.direction == 1)
        mlx->snake.y -= 2;
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
    mlx->snake.color = 0x2E8B57;
    mlx->snake.direction = 2;
    mlx->snake.score = 0;
    mlx->snake.vitesse = 100;
    mlx->food.alive = 0;
    mlx->snake.body = add_body(&(mlx->snake.x)+1, &(mlx->snake.y)+1);
    reload(mlx);
    
    mlx_hook(mlx->window, 2, 0, swap_direction, mlx); // 2 pour keypress
    //mlx_hook(mlx->window, 3, 0, swap_direction, mlx); // 3 pour keyrelease
    
    mlx_loop_hook(mlx->mlx, superloop, mlx);
    mlx_loop(mlx->mlx);
    return (0);
}