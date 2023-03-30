/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils11_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/29 18:11:26 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_up(t_game *g, int screen_w, int screen_h)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = g->m.pos_x + g->m.dir_x * g->m.move_speed;
	prueba_y = g->m.pos_y + g->m.dir_y * g->m.move_speed;
	if (g->map[(int)g->m.pos_y][(int)(prueba_x)] != '1')
	{
		g->m.pos_x = prueba_x;
	}
	if (g->map[(int)(prueba_y)][(int)(g->m.pos_x)] != '1')
	{
		g->m.pos_y = prueba_y;
	}
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, screen_w, screen_h);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, \
	&g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	ft_move_down(t_game *g, int screen_w, int screen_h)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = g->m.pos_x - g->m.dir_x * g->m.move_speed;
	prueba_y = g->m.pos_y - g->m.dir_y * g->m.move_speed;
	if (g->map[(int)g->m.pos_y][(int)(prueba_x)] != '1')
		g->m.pos_x = prueba_x;
	if (g->map[(int)(prueba_y)][(int)(g->m.pos_x)] != '1')
		g->m.pos_y = prueba_y;
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, screen_w, screen_h);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, \
	&g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	ft_move_left(t_game *g, int screen_w, int screen_h)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = g->m.pos_x + (g->m.dir_y) * g->m.move_speed;
	prueba_y = g->m.pos_y - g->m.dir_x * g->m.move_speed;
	if (g->map[(int)g->m.pos_y][(int)(prueba_x)] != '1')
		g->m.pos_x = prueba_x;
	if (g->map[(int)(prueba_y)][(int)(g->m.pos_x)] != '1')
		g->m.pos_y = prueba_y;
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, screen_w, screen_h);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, \
	&g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	ft_move_right(t_game *g, int screen_w, int screen_h)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = g->m.pos_x - (g->m.dir_y) * g->m.move_speed;
	prueba_y = g->m.pos_y + g->m.dir_x * g->m.move_speed;
	if (g->map[(int)(prueba_y)][(int)g->m.pos_x] != '1')
	{
		g->m.pos_y = prueba_y;
	}
	if (g->map[(int)(g->m.pos_y)][(int)(prueba_x)] != '1')
	{
		g->m.pos_x = prueba_x;
	}
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, screen_w, screen_h);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, \
	&g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	free_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i])
	{
		free(g->new_map[i]);
		free(g->map[i]);
		i++;
	}
	free(g->map);
	free(g->new_map);
}
