/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/30 18:59:17 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

void	ft_draw2(t_game *g, int x)
{
	g->m.camera_x = 2 * x / (double)SCREENWIDTH - 1;
	g->m.ray_dir_x = g->m.dir_x + g->m.plane_x * g->m.camera_x;
	g->m.ray_dir_y = g->m.dir_y + g->m.plane_y * g->m.camera_x;
	g->m.map_x = (int)g->m.pos_x;
	g->m.map_y = (int)g->m.pos_y;
	if (g->m.ray_dir_x == 0)
		g->m.delta_dist_x = exp(30);
	else
		g->m.delta_dist_x = fabs(1.0 / g->m.ray_dir_x);
	if (g->m.ray_dir_y == 0)
		g->m.delta_dist_y = exp(30);
	else
		g->m.delta_dist_y = fabs(1.0 / g->m.ray_dir_y);
	g->m.hit = 0;
	if (g->m.ray_dir_x < 0)
	{
		g->m.step_x = -1;
		g->m.side_dist_x = (g->m.pos_x - g->m.map_x) * g->m.delta_dist_x;
	}
	else
	{
		g->m.step_x = 1;
		g->m.side_dist_x = (g->m.map_x + 1.0 - g->m.pos_x) * g->m.delta_dist_x;
	}
}

void	ft_draw3_2(t_game *g)
{
	if (g->m.side_dist_x < g->m.side_dist_y)
	{
		g->m.side_dist_x += g->m.delta_dist_x;
		g->m.map_x += g->m.step_x;
		g->m.side = 0;
	}
	else
	{
		g->m.side_dist_y += g->m.delta_dist_y;
		g->m.map_y += g->m.step_y;
		g->m.side = 1;
	}
	if (g->map[g->m.map_y][g->m.map_x] == '1')
		g->m.hit = 1;
}

void	ft_draw3(t_game *g)
{
	if (g->m.ray_dir_y < 0)
	{
		g->m.step_y = -1;
		g->m.side_dist_y = (g->m.pos_y - g->m.map_y) * g->m.delta_dist_y;
	}
	else
	{
		g->m.step_y = 1;
		g->m.side_dist_y = (g->m.map_y + 1.0 - g->m.pos_y) * g->m.delta_dist_y;
	}
	while (g->m.hit == 0)
		ft_draw3_2(g);
}

void	ft_draw(t_game *g)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		ft_draw2(g, x);
		ft_draw3(g);
		if (g->m.side == 0)
		{
			if (g->m.ray_dir_x > 0)
				g->m.color = 1;
			else
				g->m.color = 2;
			g->m.perp_wall_dist = (g->m.side_dist_x - g->m.delta_dist_x);
		}
		else
		{
			g->m.perp_wall_dist = (g->m.side_dist_y - g->m.delta_dist_y);
			if (g->m.ray_dir_y > 0)
				g->m.color = 3;
			else
				g->m.color = 4;
		}
		x = ft_draw4(g, x);
	}
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (0);
	if (ft_read_file(&g, argv[1]) == 0)
		ft_exit_error();
	g.mlx = mlx_init();
	ft_remove_end_line(&g);
	if (ft_file_split(&g) == -1)
		ft_exit_error();
	if (ft_map_check(&g) == -1)
		ft_exit_error();
	init_variables(&g.m, &g);
	fill_new_map(&g);
	g.win = mlx_new_window(g.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	g.m.img = mlx_new_image(g.mlx, SCREENWIDTH, SCREENHEIGHT);
	g.m.addr = mlx_get_data_addr(g.m.img, &g.m.bpp, &g.m.line_length, \
	&g.m.endian);
	ft_draw(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.m.img, 0, 0);
	mlx_hook(g.win, 2, 0, &key_event, &g);
	mlx_hook(g.win, 17, 0, ft_close, &g);
	mlx_loop(g.mlx);
}
