/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/29 19:07:05 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

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

void	ft_mv_cam_left(t_game *g)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = g->m.dir_x;
	g->m.dir_x = g->m.dir_x * cos(-g->m.r_s) - g->m.dir_y * sin(-g->m.r_s);
	g->m.dir_y = old_dir_x * sin(-g->m.r_s) + g->m.dir_y * cos(-g->m.r_s);
	old_plane_x = g->m.plane_x;
	g->m.plane_x = g->m.plane_x * cos(-g->m.r_s) - g->m.plane_y * sin(-g->m.r_s);
	g->m.plane_y = old_plane_x * sin(-g->m.r_s) + g->m.plane_y * cos(-g->m.r_s);
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, SCREENWIDTH, SCREENHEIGHT);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, &g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	ft_mv_cam_right(t_game *g)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = g->m.dir_x;
	g->m.dir_x = g->m.dir_x * cos(g->m.r_s) - g->m.dir_y * sin(g->m.r_s);
	g->m.dir_y = old_dir_x * sin(g->m.r_s) + g->m.dir_y * cos(g->m.r_s);
	old_plane_x = g->m.plane_x;
	g->m.plane_x = g->m.plane_x * cos(g->m.r_s) - g->m.plane_y * sin(g->m.r_s);
	g->m.plane_y = old_plane_x * sin(g->m.r_s) + g->m.plane_y * cos(g->m.r_s);
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, SCREENWIDTH, SCREENHEIGHT);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, &g->m.line_length, &g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

int	key_event(int key_code, t_game *g)
{

	if (key_code == 53)
		//exit(0);
	ft_close(g);
	else if (key_code == 0x0D)
		ft_move_up(g, SCREENWIDTH, SCREENHEIGHT);
	else if (key_code == 0x01)
		ft_move_down(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 2)
		ft_move_right(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 0)
		ft_move_left(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 124)
		ft_mv_cam_left(g);
	if (key_code == 123)
		ft_mv_cam_right(g);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_mlx_pixel_color(t_img *tex, int x, int y)
{
	char			*dst;
	int				offset;
	unsigned int	color;

	offset = (y * tex->line_length + x * (tex->bpp / 8));
	dst = tex->addr + offset;
	color = *(unsigned int *)dst;
	return (color);
}

static void	draw_column(t_game *g, int x, int y, t_img *tex)
{
	my_mlx_pixel_put(&g->m, x, y, get_mlx_pixel_color(tex, g->tex_x, g->tex_y));
}

void	ver_line(t_data *m, int x, t_game *g)
{
	int	i;

	i = 0;
	while (i < m->draw_start)
		my_mlx_pixel_put(m, x, i++, g->c_col.color);
	while (i < SCREENHEIGHT)
	{
		g->tex_y = (int)g->tex_pos & (g->tex_height - 1);
		g->tex_pos += g->step;
		if (g->m.color == 1)
			draw_column(g, x, i, &g->no);
		if (g->m.color == 2)
			draw_column(g, x, i, &g->we);
		if (g->m.color == 3)
			draw_column(g, x, i, &g->so);
		if (g->m.color == 4)
			draw_column(g, x, i, &g->ea);
		i ++;
	}
	while (m->draw_end < SCREENHEIGHT)
		my_mlx_pixel_put(m, x, m->draw_end++, g->f_col.color);
}

char	ft_find_pj(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g->map[i])
	{
		while (g->map[i][j])
		{
			if (g->map[i][j] == 'E' || g->map[i][j] == 'N' || g->map[i][j] == 'S' || g->map[i][j] == 'W')
				return (g->map[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	return ('X');
}

void	init_variables(t_data *m, t_game *game)
{
	char	a;

	a = ft_find_pj(game);
	m->pos_x = game->p.x + 0.5;
	m->pos_y = game->p.y + 0.5;
	game->tex_height = 64;
	game->tex_width = 64;
	if (a == 'E')
	{
		m->dir_x = 1;
		m->dir_y = 0;
		m->plane_x = 0;
		m->plane_y = 0.66;
	}
	else if (a == 'W')
	{
		m->dir_x = -1;
		m->dir_y = 0;
		m->plane_x = 0;
		m->plane_y = -0.66;
	}
	else if (a == 'N')
	{
		m->dir_x = 0;
		m->dir_y = -1;
		m->plane_x = 0.66;
		m->plane_y = 0;
	}
	else if (a == 'S')
	{
		m->dir_x = 0;
		m->dir_y = 1;
		m->plane_x = -0.66;
		m->plane_y = 0;
	}
	m->time = 0;
	m->old_time = 0;
	m->r_s = 25;
	m->move_speed = 0.1;
}

void	ft_draw(t_game *g)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
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
		g->m.line_h = (int)(SCREENHEIGHT / g->m.perp_wall_dist);
		g->m.draw_start = -g->m.line_h / 2 + SCREENHEIGHT / 2;
		if (g->m.draw_start < 0)
			g->m.draw_start = 0;
		g->m.draw_end = g->m.line_h / 2 + SCREENHEIGHT / 2;
		if (g->m.draw_end >= SCREENHEIGHT)
			g->m.draw_end = SCREENHEIGHT - 1;
		if (g->m.side == 0)
			g->wallx = g->m.pos_y + g->m.perp_wall_dist * g->m.ray_dir_y;
		else
			g->wallx = g->m.pos_x + g->m.perp_wall_dist * g->m.ray_dir_x;
		g->wallx -= floor(g->wallx);
		g->tex_x = (int)(g->wallx * (double)g->tex_width);
		if (g->m.side == 0 && g->m.ray_dir_x > 0)
			g->tex_x = g->tex_width - g->tex_x - 1;
		if (g->m.side == 1 && g->m.ray_dir_y < 0)
			g->tex_x = g->tex_width - g->tex_x - 1;
		g->step = 1.0 * g->tex_height / g->m.line_h;
		g->tex_pos = (g->m.draw_start - SCREENHEIGHT / 2 + g->m.line_h / 2) * g->step;
		ver_line(&g->m, x, g);
		x ++;
	}
}

void	fill_new_map(t_game *game)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	j = 0;
	while (game->map[j])
		j ++;
	game->new_map = (int **)malloc(sizeof(int *) * j);
	while (w < j)
	{
		while (game->map[w][i])
			i ++;
		game->new_map[w] = (int *)malloc(sizeof(int) * i);
		i = 0;
		while (game->map[w][i])
		{
			if (game->map[w][i] == '1')
				game->new_map[w][i] = 1;
			else
				game->new_map[w][i] = 0;
			i ++;
		}
		i = 0;
		w ++;
	}
}

int	main(int argc, char **argv)
{
	t_game	g;
	int		i;

	i = 0;
	if (argc < 2)
		return (0);
	if (ft_read_file(&g, argv[1]) == 0)
		return (0);
	while (i < g.mh)
		i++;
	g.mlx = mlx_init();
	ft_remove_end_line(&g);
	if (ft_file_split(&g) == -1)
		return (-1);
	if (ft_map_check(&g) == -1)
		return (-1);
	init_variables(&g.m, &g);
	fill_new_map(&g);
	g.win = mlx_new_window(g.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	g.m.img = mlx_new_image(g.mlx, SCREENWIDTH, SCREENHEIGHT);
	g.m.addr = mlx_get_data_addr(g.m.img, &g.m.bpp, &g.m.line_length, &g.m.endian);
	ft_draw(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.m.img, 0, 0);
	mlx_hook(g.win, 2, 0, &key_event, &g);
	mlx_hook(g.win, 17, 0, ft_close, &g);
	mlx_loop(g.mlx);
}
