/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:39 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/09 18:37:04 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "mlx/mlx.h"

void	ft_move_up(t_game *g, int key)
{
	key = 0;//!
	if (g->map[(int)g->p.y - 1][(int)g->p.x] == '0')
	{
		g->mv++;
		//my_mlx_pixel_put(g->data, (int)g->p.x, (int)g->p.y, 0xFF0000);
		//my_mlx_pixel_put(g->data, (int)g->p.posX, (int)g->p.posY, 0x000000);
	//	g->map[g->p.y - 1][g->p.x] = 'P';
	//	g->map[g->p.y][g->p.x] = '0';
		g->p.y -= 0.05;
	}
	else if (g->map[(int)g->p.y - 1][(int)g->p.x] == 'E')
		ft_close(g);
}

void	ft_move_down(t_game *g, int key)
{
	key = 0;//!
	if (g->map[(int)g->p.y + 1][(int)g->p.x] == '0')
	{
		g->mv++;
	//	g->map[g->p.y + 1][g->p.x] = 'P';
	//	g->map[g->p.y][g->p.x] = '0';
		g->p.y += 0.05;
	}
	else if (g->map[(int)g->p.y + 1][(int)g->p.x] == 'E')
		ft_close(g);
}

void	ft_move_left(t_game *g, int key)
{
	key = 0;//!
	if (g->map[(int)g->p.y][(int)g->p.x - 1] == '0')
	{
		g->mv++;
	//	g->map[g->p.y][g->p.x - 1] = 'P';
	//	g->map[g->p.y][g->p.x] = '0';
		g->p.x -= 0.05;
	}
	else if (g->map[(int)g->p.y][(int)g->p.x - 1] == 'E')
		ft_close(g);
}

void	ft_move_right(t_game *g, int key)
{
	key = 0;//!
	if (g->map[(int)g->p.y][(int)g->p.x + 1] == '0')
	{
		g->mv++;
//		g->map[g->p.y][g->p.x + 1] = 'P';
//		g->map[g->p.y][g->p.x] = '0';
		g->p.x += 0.05;
	}
	else if (g->map[(int)g->p.y][(int)g->p.x + 1] == 'E')
		ft_close(g);
}

int	ft_controlls(int keykode, t_game *g)
{
	//printf("tecla = %d\n")
	if (keykode == 0x35)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	else if (keykode == 0x0D)
		ft_move_up(g, keykode);
	else if (keykode == 0x00)
		ft_move_left(g, keykode);
	else if (keykode == 0x01)
		ft_move_down(g, keykode);
	else if (keykode == 0x02)
		ft_move_right(g, keykode);
	system("clear");
	printf("mv = %d\n", g->mv);
	return (0);
}
