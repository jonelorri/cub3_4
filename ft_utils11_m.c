/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils8_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/28 18:32:07 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_up(t_game *game, int screen_w, int screen_h)
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
	game->m.img = mlx_new_image(game->mlx, screen_w, screen_h);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bpp, \
	&game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_down(t_game *game, int screen_w, int screen_h)
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
	game->m.img = mlx_new_image(game->mlx, screen_w, screen_h);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bpp, \
	&game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_left(t_game *game, int screen_w, int screen_h)
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
	game->m.img = mlx_new_image(game->mlx, screen_w, screen_h);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bpp, \
	&game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_right(t_game *game, int screen_w, int screen_h)
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
	game->m.img = mlx_new_image(game->mlx, screen_w, screen_h);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bpp, \
	&game->m.line_length, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}
