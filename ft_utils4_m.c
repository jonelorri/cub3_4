/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/29 19:49:36 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first2_map_check(char **map, int mh, int x, int y)
{
	if (y < mh - 1 && x > (int)ft_strlen(map[y + 1]))
	{
		if (ft_close_map_ext(map[y] + x))
			return (1);
	}
	return (0);
}

int	ft_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	free_map(g);
	system("leaks Cub3d");
	exit(0);
}

void	ft_write_hex_c(size_t a, int w, t_game *game)
{
	char			*hex;
	char			*hex2;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';
	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	if (game->c_col.init == 0)
	{
		game->c_col.init++;
		hex2[0] = hex[a];
		hex2[1] = '\0';
		game->c_col.col = ft_strjoin("0x", hex2);
	}
	else
	{
		game->c_col.col = ft_strjoin(game->c_col.col, hex2);
	}
}

void	ft_hex_c(size_t nb, int a, t_game *game)
{
	if (nb >= 0 && nb < 16)
		ft_write_hex_c(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_c(nb / 16, a, game);
		ft_write_hex_c(nb % 16, a, game);
	}
}

void	ft_color_hex_c(t_game *game)
{
	game->c_col.init = 0;
	if (game->c_col.r < 16)
		ft_hex_c(game->c_col.r, 1, game);
	else
		ft_hex_c(game->c_col.r, 0, game);
	if (game->f_col.g < 16)
		ft_hex_c(game->c_col.g, 1, game);
	else
		ft_hex_c(game->c_col.g, 0, game);
	if (game->c_col.b < 16)
		ft_hex_c(game->c_col.b, 1, game);
	else
		ft_hex_c(game->c_col.b, 0, game);
}
