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

void	ft_write_hex_f(size_t a, int w, t_game *game)
{
	char	*hex;
	char	*hex2;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';
	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	if (game->f_col.init == 0)
	{
		game->f_col.init++;
		game->f_col.col = ft_strjoin("0x", hex2);
	}
	else
	{
		game->f_col.col = ft_strjoin(game->f_col.col, hex2);
	}
}

void	ft_hex_f(size_t nb, int a, t_game *game)
{
	if (nb >= 0 && nb < 16)
		ft_write_hex_f(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_f(nb / 16, a, game);
		ft_write_hex_f(nb % 16, a, game);
	}
}

void	ft_color_hex(t_game *game)
{
	game->f_col.init = 0;
	if (game->f_col.r < 16)
		ft_hex_f(game->f_col.r, 1, game);
	else
		ft_hex_f(game->f_col.r, 0, game);
	if (game->f_col.g < 16)
		ft_hex_f(game->f_col.g, 1, game);
	else
		ft_hex_f(game->f_col.g, 0, game);
	if (game->f_col.b < 16)
		ft_hex_f(game->f_col.b, 1, game);
	else
		ft_hex_f(game->f_col.b, 0, game);
}

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	t_map_trim(char **str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		ptr = ft_strtrim(str[i], " ");
		free (str[i]);
		str[i] = ptr;
		i++;
	}
}
