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

void	ft_get_map3_2(t_game *game, int i)
{
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
		ft_get_map3_2(game, i);
		i++;
	}
	if (game->so_check + game->ea_check + game->we_check \
	+ game->no_check + game->c_check + game->f_check != 6)
	{
		printf("Error, invalid map\n");
		return (1);
	}
	return (0);
}

void	ft_check_text2(t_game *game)
{
	game->we.addr = mlx_get_data_addr(game->we.img, &game->we.bpp, \
	&game->we.line_length, &game->we.endian);
	if (game->ea_tex)
		game->ea.img = mlx_xpm_file_to_image(game->mlx, game->ea_tex, \
		&game->ea.w, &game->ea.h);
}

int	ft_check_tex(t_game *game)
{
	if (game->no_tex)
		game->no.img = mlx_xpm_file_to_image(game->mlx, game->no_tex, \
		&game->no.w, &game->no.h);
	if (!game->no.img || !game->no_tex)
		return (-1);
	game->no.addr = mlx_get_data_addr(game->no.img, &game->no.bpp, \
	&game->no.line_length, &game->no.endian);
	if (game->so_tex)
		game->so.img = mlx_xpm_file_to_image(game->mlx, game->so_tex, \
		&game->so.w, &game->so.h);
	if (!game->so.img || !game->so_tex)
		return (-1);
	game->so.addr = mlx_get_data_addr(game->so.img, &game->so.bpp, \
	&game->so.line_length, &game->so.endian);
	if (game->we_tex)
		game->we.img = mlx_xpm_file_to_image(game->mlx, game->we_tex, \
		&game->we.w, &game->we.h);
	if (!game->we.img || !game->we_tex)
		return (-1);
	ft_check_text2(game);
	if (!game->ea.img || !game->ea_tex)
		return (-1);
	game->ea.addr = mlx_get_data_addr(game->ea.img, &game->ea.bpp, \
	&game->ea.line_length, &game->ea.endian);
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
