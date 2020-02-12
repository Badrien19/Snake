/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:48:01 by badrien           #+#    #+#             */
/*   Updated: 2020/02/12 17:07:42 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../libft/libft.h"

#define S_SNAKE_HEAD 9
#define S_SNAKE_BODY 7
#define S_SNAKE_LAST 5

typedef struct s_food
{
    int x;
    int y;
    int color;
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

void aff_block(t_mlx *mlx, int size, t_body *body, int color)
{   
    int i = (size/2) * -1;
    int y = (size/2) * -1;
    while(i < (size/2) + 1)
    {
        mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, color);
        while(y < (size/2) + 1)
        {
            mlx_pixel_put(mlx->mlx, mlx->window, body->x + i, body->y + y, color);
            y++;      
        }
    y = (size/2) * -1;
    i++;
    }
}

void aff_head(t_mlx *mlx)
{
    int x = -4;
    int y = -4;
    while(x < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + x, mlx->snake.y + y, mlx->snake.color);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + x, mlx->snake.y + y, mlx->snake.color);
            y++;      
       }
    y = -4;
    x++;
    }

    /* Affichage yeux et langue*/
    if(mlx->snake.direction == 4) // haut
    {
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 2, mlx->snake.y + 2, 0xFFFF00);        
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 2, mlx->snake.y - 2, 0xFFFF00);

        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 5, mlx->snake.y, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 5, mlx->snake.y - 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 5, mlx->snake.y + 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 6, mlx->snake.y - 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 6, mlx->snake.y + 1, 0xFF0000);
    }
    if(mlx->snake.direction == 3) // bas
    {
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 2, mlx->snake.y - 2, 0xFFFF00);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 2, mlx->snake.y + 2, 0xFFFF00);

        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 5, mlx->snake.y, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 5, mlx->snake.y - 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 5, mlx->snake.y + 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 6, mlx->snake.y - 1, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 6, mlx->snake.y + 1, 0xFF0000);
    }
    if(mlx->snake.direction == 2) // bas
    {
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 2, mlx->snake.y + 2, 0xFFFF00);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 2, mlx->snake.y + 2, 0xFFFF00);

        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x , mlx->snake.y + 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 1, mlx->snake.y + 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 1, mlx->snake.y + 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 1, mlx->snake.y + 6, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 1, mlx->snake.y + 6, 0xFF0000);
    }
    if(mlx->snake.direction == 1) // haut
    {
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 2, mlx->snake.y - 2, 0xFFFF00);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 2, mlx->snake.y - 2, 0xFFFF00);

        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x , mlx->snake.y - 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 1, mlx->snake.y - 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 1, mlx->snake.y - 5, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x - 1, mlx->snake.y - 6, 0xFF0000);
        mlx_pixel_put(mlx->mlx, mlx->window, mlx->snake.x + 1, mlx->snake.y - 6, 0xFF0000);
    }
}

void aff_snake(t_mlx *mlx)
{
    int i;
    int y;

    t_body *body;
    body = mlx->snake.body;

    while(body->next != NULL) // tous les block
    {
        aff_block(mlx, S_SNAKE_BODY, body, 0x9FE855);
        body = body->next;
    }

    aff_block(mlx, S_SNAKE_LAST, body, 0xE58B05); //le dernier block
    aff_head(mlx);
}

void aff_food(t_mlx *mlx)
{
    int i;
    int y;

    i = -4;
    y = -4;
    while(i < 5)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, mlx->food.color);
       while(y < 5)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->food.x + i, mlx->food.y + y, mlx->food.color);
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
    mlx_string_put(mlx->mlx, mlx->window, 50, 40, 0x00FF00, "Snake 1.0 :");

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
    
    mlx_string_put(mlx->mlx, mlx->window, 50, 380, 0x00FF00, "Press \"ESC\" to quit :C");
}

void food(t_mlx *mlx)
{
    if(mlx->food.alive == 1)
        return;
    srand(time(NULL));
    mlx->food.x= (rand() % (341 - 59 + 1)) + 59; // (rand() % (max - min + 1)) + min;
    mlx->food.y= (rand() % (341 - 59 + 1)) + 59;
    mlx->food.alive = 1;
    mlx->food.color = 0xE30A0A;
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
    
    next = mlx->snake.body->next;
    if(!(mlx->snake.body->next == NULL))
    while(next != NULL)
    {
        if((mlx->snake.x >= next->x && mlx->snake.x <= next->x ) && (mlx->snake.y >= next->y && mlx->snake.y <= next->y ))
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
    if(keycode == 258 && mlx->go == 0)
        mlx->snake.direction = 7;
    if(keycode == 36)
        mlx->go = 1;
    if(keycode == 53)
        mlx->snake.direction = 6;
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
    if(body->first < 2)
        body->first += 1;
    else
    {
        body->x = x;
        body->y = y;
        body->first = 0;
    }
    return (0);
}

int lauch(void);

int superloop(t_mlx *mlx)
{
    usleep(mlx->snake.vitesse);

    if(mlx->go == 0)
        return (0);

    inc_tail(mlx, mlx->snake.body, mlx->snake.x, mlx->snake.y);

    mlx->snake.body->x = mlx->snake.x;
    mlx->snake.body->y = mlx->snake.y;

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
        mlx_clear_window(mlx->mlx, mlx->window);
        mlx_string_put(mlx->mlx,mlx->window,50,200,0xFFFFFF,"press 'maj droite' et 'enter droite'");
        mlx_string_put(mlx->mlx,mlx->window,110,220,0xFFFFFF,"pour relancer le jeu");
        mlx->go = 0;
    }
    if(mlx->snake.direction == 6)
    {
        mlx->go = 0;
        free(mlx);
        mlx_destroy_window(mlx->mlx, mlx->window);
        exit(-1);
    }
    if(mlx->snake.direction == 7 )//&& mlx->go == 0)
    {
        reload(mlx);
        //mlx_clear_window(mlx->mlx, mlx->window);
        //mlx_string_put(mlx->mlx,mlx->window,50,200,0xFFFFFF,"press 'maj droite' pour relancer le jeu");
        lauch();
    }
    if(mlx->go != 0)
        reload(mlx);
    return (0);
}

int setup(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->window = mlx_new_window(mlx->mlx, 400, 400, "Snake 1.0");
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
    return (0);
}

int lauch(void)
{
    t_mlx *mlx;
    mlx = (t_mlx *) malloc(sizeof(t_mlx));
    
    setup(mlx);
    
    mlx_hook(mlx->window, 2, 0, swap_direction, mlx); // 2 pour keypress
    mlx_loop_hook(mlx->mlx, superloop, mlx);
    mlx_loop(mlx->mlx);
    return (0);
}

int main(void)
{
    lauch();
}