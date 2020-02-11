/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:36:21 by badrien           #+#    #+#             */
/*   Updated: 2020/02/10 13:48:47 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_pixel
{
    int x;
    int y;
    int color;
}               t_pixel;

typedef struct s_mlx
{
    void *mlx;
    void *window;
    t_pixel player;
}               t_mlx;

void aff_player(t_mlx *mlx)
{
    int i;
    int y;

    i = 0;
    y = 0;
    while(i < 8)
    {
       mlx_pixel_put(mlx->mlx, mlx->window, mlx->player.x + i, mlx->player.y + y, mlx->player.color);
       while(y < 8)
       {
           mlx_pixel_put(mlx->mlx, mlx->window, mlx->player.x + i, mlx->player.y + y, mlx->player.color);
            y++;      
       }
    y = 0;
    i++;
    }
}

void aff_bordure(t_mlx *mlx)
{
    int x = 50;
    int y = 50;
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

void reload(t_mlx *mlx)
{
    mlx_clear_window(mlx->mlx, mlx->window);
    aff_player(mlx);
    aff_bordure(mlx);

}

int affich(int keycode, t_mlx *mlx)
{
    //printf("keycode : %d\n", keycode);
    
    if (keycode == 126)
        mlx->player.y -= 2;
    if (keycode == 125)
        mlx->player.y += 2;
    if (keycode == 123)
        mlx->player.x -= 2;
    if (keycode == 124)
        mlx->player.x += 2;
    reload(mlx);
    return(0);
}

int main(void)
{
    t_mlx *mlx;

    mlx = (t_mlx *) malloc(sizeof(t_mlx));


    mlx->mlx = mlx_init();
    mlx->window = mlx_new_window(mlx->mlx, 400, 400, "Belle fenetre");

    mlx->player.x = 200;
    mlx->player.y = 200;
    mlx->player.color = 0xF8F4F8;

    reload(mlx);

    mlx_hook(mlx->window, 2, 0, affich, mlx); // 2 pour keypress
    mlx_hook(mlx->window, 3, 0, affich, mlx); // 3 pour keyrelease
    mlx_loop(mlx->mlx);
    return (0);
}

