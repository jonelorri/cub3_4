/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/09 17:17:10 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

int	ft_get_map2(t_game *game)
{
	int	i;

	i = 0;
	ft_file_copy(game);
	t_map_trim(game->file_save);
	while (game->file_save[i] && game->file_save[i][0] && game->file_save[i][0] != '1' )
	{
		i++;
	}
	while (game->file_save[i])
	{
		if (ft_strchr(game->file_save[i], '\n'))
		{
			printf("Error, invalid map\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_get_map3(t_game *game)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (game->file_save[i][0] && game->file_save[i][0] != '1')
	{
		if (ft_strstr(game->file_save[i], "NO "))
		{
			game->no_check = 1;
			n++;
		}
		if (ft_strstr(game->file_save[i], "EA "))
			game->ea_check = 1;
		if (ft_strstr(game->file_save[i], "WE "))
			game->we_check = 1;
		if (ft_strstr(game->file_save[i], "SO "))
			game->so_check = 1;
		if (ft_strstr(game->file_save[i], "F "))
			game->f_check = 1;
		if (ft_strstr(game->file_save[i], "C "))
			game->c_check = 1;
		i++;
	}
	if (game->so_check + game->ea_check + game->we_check + game->no_check + game->c_check + game->f_check != 6)
	{
		printf("Error, invalid map\n");
		return (1);
	}
	return (0);
}

int	ft_check_tex(t_game *game)
{
	if (game->no_tex)
	{
		game->no.img = mlx_xpm_file_to_image(game->mlx, game->no_tex, &game->no.w, &game->no.h);
		game->no.line_length = 0;
		game->no.bits_per_pixel = 0;
		game->no.endian = 0;
	}
	if (!game->no.img || !game->no_tex)
		return (-1);
	game->no.addr = mlx_get_data_addr(game->no.img, &game->no.bits_per_pixel, &game->no.line_length, &game->no.endian);
	if (game->so_tex)
	{
		game->so.img = mlx_xpm_file_to_image(game->mlx, game->so_tex, &game->so.w, &game->so.h);
		game->so.line_length = 0;
		game->so.bits_per_pixel = 0;
		game->so.endian = 0;
	}
	if (!game->so.img || !game->so_tex)
		return (-1);
	game->so.addr = mlx_get_data_addr(game->so.img, &game->so.bits_per_pixel, &game->so.line_length, &game->so.endian);
	if (game->we_tex)
	{
		game->we.img = mlx_xpm_file_to_image(game->mlx, game->we_tex, &game->we.w, &game->we.h);
		game->we.line_length = 0;
		game->we.bits_per_pixel = 0;
		game->we.endian = 0;
	}
	if (!game->we.img || !game->we_tex)
		return (-1);
	game->we.addr = mlx_get_data_addr(game->we.img, &game->we.bits_per_pixel, &game->we.line_length, &game->we.endian);
	if (game->ea_tex)
	{
		game->ea.img = mlx_xpm_file_to_image(game->mlx, game->ea_tex, &game->ea.w, &game->ea.h);
		game->ea.line_length = 0;
		game->ea.bits_per_pixel = 0;
		game->ea.endian = 0;
	}
	if (!game->ea.img || !game->ea_tex)
		return (-1);
	game->ea.addr = mlx_get_data_addr(game->ea.img, &game->ea.bits_per_pixel, &game->ea.line_length, &game->ea.endian);
	return (0);
}

int	ft_check_color_com(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && (int)ft_strlen(str) > i)
			if (str[i + 1] < '0' || str[i + 1] > '9')
				return (1);
		i++;
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_get_color_f(t_game *game)
{
	char	**col_mat;

	if (ft_check_color_com(game->col_f))
		return (-1);
	col_mat = ft_split(game->col_f, ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->f_col.r = ft_atoi(col_mat[0]);
	game->f_col.g = ft_atoi(col_mat[1]);
	game->f_col.b = ft_atoi(col_mat[2]);
	game->f_col.color = create_trgb(1, game->f_col.r, game->f_col.g, game->f_col.b);
	free_matrix(col_mat);
	if (game->f_col.r > 255 || game->f_col.r < 0)
		return (-1);
	if (game->f_col.g > 255 || game->f_col.g < 0)
		return (-1);
	if (game->f_col.b > 255 || game->f_col.b < 0)
		return (-1);
	return (0);
}

int	ft_get_color_c(t_game *game)
{
	char	**col_mat;	

	if (ft_check_color_com(game->col_c))
		return (-1);
	col_mat = ft_split(game->col_c, ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->c_col.r = ft_atoi(col_mat[0]);
	game->c_col.g = ft_atoi(col_mat[1]);
	game->c_col.b = ft_atoi(col_mat[2]);
	game->c_col.color = create_trgb(1, game->c_col.r, game->c_col.g, game->c_col.b);
	free_matrix(col_mat);
	if (!col_mat)
		return (-1);
	if (game->c_col.r > 255 || game->c_col.r < 0)
		return (-1);
	if (game->c_col.g > 255 || game->c_col.g < 0)
		return (-1);
	if (game->c_col.b > 255 || game->c_col.b < 0)
		return (-1);
	return (0);
}

int	ft_file_split(t_game *game)
{
	game->no_tex = ft_find_str_matrix2("NO ", game->file);
	game->so_tex = ft_find_str_matrix2("SO ", game->file);
	game->we_tex = ft_find_str_matrix2("WE ", game->file);
	game->ea_tex = ft_find_str_matrix2("EA ", game->file);
	if (ft_check_tex(game) == -1)
	{
		printf("\nError with textures\n");
		return (-1);
	}
	game->col_f = ft_find_str_matrix2("F ", game->file);
	game->col_c = ft_find_str_matrix2("C ", game->file);
	if (!game->col_f || !game->col_c || (ft_get_color_c(game) == -1) || (ft_get_color_f(game) == -1))
	{
		printf("\nError with colors\n");
		return (-1);
	}
	ft_color_hex(game);
	ft_color_hex_c(game);
	if (ft_get_map2(game))
		return (-1);
	game->map = ft_get_map(game);
	if (!game->map)
		return (-1);
	if (ft_get_map3(game))
		return (-1);
	game->mv = 0;
	return (0);
}

void	ft_move_up(t_game *game)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = game->m.pos_x + game->m.dir_x * game->m.move_speed;
	prueba_y = game->m.pos_y + game->m.dir_y * game->m.move_speed;
	if (game->map[(int)game->m.pos_y][(int)(prueba_x)] != '1')
	{
		game->m.pos_x = prueba_x;
	}
	if (game->map[(int)(prueba_y)][(int)(game->m.pos_x)] != '1')
	{
		game->m.pos_y = prueba_y;
	}
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_down(t_game *game)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = game->m.pos_x - game->m.dir_x * game->m.move_speed;
	prueba_y = game->m.pos_y - game->m.dir_y * game->m.move_speed;
	if (game->map[(int)game->m.pos_y][(int)(prueba_x)] != '1')
		game->m.pos_x = prueba_x;
	if (game->map[(int)(prueba_y)][(int)(game->m.pos_x)] != '1')
		game->m.pos_y = prueba_y;
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_left(t_game *game)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = game->m.pos_x + (game->m.dir_y) * game->m.move_speed;
	prueba_y = game->m.pos_y - game->m.dir_x * game->m.move_speed;
	if (game->map[(int)game->m.pos_y][(int)(prueba_x)] != '1')
		game->m.pos_x = prueba_x;
	if (game->map[(int)(prueba_y)][(int)(game->m.pos_x)] != '1')
		game->m.pos_y = prueba_y;
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_right(t_game *game)
{
	double	prueba_x;
	double	prueba_y;

	prueba_x = game->m.pos_x - (game->m.dir_y) * game->m.move_speed;
	prueba_y = game->m.pos_y + game->m.dir_x * game->m.move_speed;
	if (game->map[(int)(prueba_y)][(int)game->m.pos_x] != '1')
	{
		game->m.pos_y = prueba_y;
	}
	if (game->map[(int)(game->m.pos_y)][(int)(prueba_x)] != '1')
	{
		game->m.pos_x = prueba_x;
	}
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

int	key_event(int key_code, t_game *game)
{
	double	old_plane_x;
	double	old_dir_x;

	if (key_code == 53)
		exit(0);
	else if (key_code == 0x0D)
		ft_move_up(game);
	else if (key_code == 0x01)
		ft_move_down(game);
	if (key_code == 2)
		ft_move_right(game);
	if (key_code == 0)
		ft_move_left(game);
	if (key_code == 124)
	{
		old_dir_x = game->m.dir_x;
		game->m.dir_x = game->m.dir_x * cos(-game->m.rot_speed) - game->m.dir_y * sin(-game->m.rot_speed);
		game->m.dir_y = old_dir_x * sin(-game->m.rot_speed) + game->m.dir_y * cos(-game->m.rot_speed);
		old_plane_x = game->m.plane_x;
		game->m.plane_x = game->m.plane_x * cos(-game->m.rot_speed) - game->m.plane_y * sin(-game->m.rot_speed);
		game->m.plane_y = old_plane_x * sin(-game->m.rot_speed) + game->m.plane_y * cos(-game->m.rot_speed);
		mlx_destroy_image(game->mlx, game->m.img);
		game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
		game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
		ft_draw(game);
		mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
	}
	else if (key_code == 123)
	{
		old_dir_x = game->m.dir_x;
		game->m.dir_x = game->m.dir_x * cos(game->m.rot_speed) - game->m.dir_y * sin(game->m.rot_speed);
		game->m.dir_y = old_dir_x * sin(game->m.rot_speed) + game->m.dir_y * cos(game->m.rot_speed);
		old_plane_x = game->m.plane_x;
		game->m.plane_x = game->m.plane_x * cos(game->m.rot_speed) - game->m.plane_y * sin(game->m.rot_speed);
		game->m.plane_y = old_plane_x * sin(game->m.rot_speed) + game->m.plane_y * cos(game->m.rot_speed);
		mlx_destroy_image(game->mlx, game->m.img);
		game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
		game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.line_length, &game->m.endian);
		ft_draw(game);
		mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_mlx_pixel_color(t_img *tex, int x, int y)
{
	char			*dst;
	int				offset;
	unsigned int	color;

	offset = (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	dst = tex->addr + offset;
	color = *(unsigned int *)dst;
	return (color);
}

static void	draw_column(t_game *game, int x, int y, t_img *tex)
{
	my_mlx_pixel_put(&game->m, x, y, get_mlx_pixel_color(tex, game->tex_x, game->tex_y));
}

void	ver_line(t_data *m, int x, t_game *game)
{
	int	i;

	i = 0;
	while (i < m->draw_start)
	{
		my_mlx_pixel_put(m, x, i, game->c_col.color);
		i ++;
	}
	while (i < SCREENHEIGHT)
	{
		game->tex_y = (int)game->tex_pos & (game->tex_height - 1);
		game->tex_pos += game->step;
		if (game->m.color == 1)
			draw_column(game, x, i, &game->no);
		if (game->m.color == 2)
			draw_column(game, x, i, &game->we);
		if (game->m.color == 3)
			draw_column(game, x, i, &game->so);
		if (game->m.color == 4)
			draw_column(game, x, i, &game->ea);
		i ++;
	}
	while (m->draw_end < SCREENHEIGHT)
	{
		my_mlx_pixel_put(m, x, m->draw_end, game->f_col.color);
		m->draw_end ++;
	}
}

char	ft_find_pj(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E' || game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W')
				return (game->map[i][j]);
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
	m->rot_speed = 25;
	m->move_speed = 0.1;
}

void	ft_draw(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		game->m.camera_x = 2 * x / (double)SCREENWIDTH - 1;
		game->m.ray_dir_x = game->m.dir_x + game->m.plane_x * game->m.camera_x;
		game->m.ray_dir_y = game->m.dir_y + game->m.plane_y * game->m.camera_x;
		game->m.map_x = (int)game->m.pos_x;
		game->m.map_y = (int)game->m.pos_y;
		if (game->m.ray_dir_x == 0)
			game->m.delta_dist_x = exp(30);
		else
			game->m.delta_dist_x = fabs(1.0 / game->m.ray_dir_x);
		if (game->m.ray_dir_y == 0)
			game->m.delta_dist_y = exp(30);
		else
			game->m.delta_dist_y = fabs(1.0 / game->m.ray_dir_y);
		game->m.hit = 0;
		if (game->m.ray_dir_x < 0)
		{
			game->m.step_x = -1;
			game->m.side_dist_x = (game->m.pos_x - game->m.map_x) * game->m.delta_dist_x;
		}
		else
		{
			game->m.step_x = 1;
			game->m.side_dist_x = (game->m.map_x + 1.0 - game->m.pos_x) * game->m.delta_dist_x;
		}
		if (game->m.ray_dir_y < 0)
		{
			game->m.step_y = -1;
			game->m.side_dist_y = (game->m.pos_y - game->m.map_y) * game->m.delta_dist_y;
		}
		else
		{
			game->m.step_y = 1;
			game->m.side_dist_y = (game->m.map_y + 1.0 - game->m.pos_y) * game->m.delta_dist_y;
		}
		while (game->m.hit == 0)
		{
			if (game->m.side_dist_x < game->m.side_dist_y)
			{
				game->m.side_dist_x += game->m.delta_dist_x;
				game->m.map_x += game->m.step_x;
				game->m.side = 0;
			}
			else
			{
				game->m.side_dist_y += game->m.delta_dist_y;
				game->m.map_y += game->m.step_y;
				game->m.side = 1;
			}
			if (game->map[game->m.map_y][game->m.map_x] == '1')
				game->m.hit = 1;
		}
		if (game->m.side == 0)
		{
			if (game->m.ray_dir_x > 0)
				game->m.color = 1;
			else
				game->m.color = 2;
			game->m.perp_wall_dist = (game->m.side_dist_x - game->m.delta_dist_x);
		}
		else
		{
			game->m.perp_wall_dist = (game->m.side_dist_y - game->m.delta_dist_y);
			if (game->m.ray_dir_y > 0)
				game->m.color = 3;
			else
				game->m.color = 4;
		}
		game->m.line_h = (int)(SCREENHEIGHT / game->m.perp_wall_dist);
		game->m.draw_start = -game->m.line_h / 2 + SCREENHEIGHT / 2;
		if (game->m.draw_start < 0)
			game->m.draw_start = 0;
		game->m.draw_end = game->m.line_h / 2 + SCREENHEIGHT / 2;
		if (game->m.draw_end >= SCREENHEIGHT)
			game->m.draw_end = SCREENHEIGHT - 1;
		if (game->m.side == 0)
			game->wallx = game->m.pos_y + game->m.perp_wall_dist * game->m.ray_dir_y;
		else
			game->wallx = game->m.pos_x + game->m.perp_wall_dist * game->m.ray_dir_x;
		game->wallx -= floor(game->wallx);
		game->tex_x = (int)(game->wallx * (double)game->tex_width);
		if (game->m.side == 0 && game->m.ray_dir_x > 0)
			game->tex_x = game->tex_width - game->tex_x - 1;
		if (game->m.side == 1 && game->m.ray_dir_y < 0)
			game->tex_x = game->tex_width - game->tex_x - 1;
		game->step = 1.0 * game->tex_height / game->m.line_h;
		game->tex_pos = (game->m.draw_start - SCREENHEIGHT / 2 + game->m.line_h / 2) * game->step;
		ver_line(&game->m, x, game);
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
	t_game	game;
	int		i;

	i = 0;
	if (argc < 2)
		return (0);
	if (ft_read_file(&game, argv[1]) == 0)
		return (0);
	while (i < game.mh)
		i++;
	game.mlx = mlx_init();
	ft_remove_end_line(&game);
	if (ft_file_split(&game) == -1)
		return (-1);
	if (ft_map_check(&game) == -1)
		return (-1);
	init_variables(&game.m, &game);
	fill_new_map(&game);
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	game.m.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	game.m.addr = mlx_get_data_addr(game.m.img, &game.m.bits_per_pixel, &game.m.line_length, &game.m.endian);
	ft_draw(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.m.img, 0, 0);
	mlx_hook(game.win, 2, 0, &key_event, &game);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_loop(game.mlx);
}
