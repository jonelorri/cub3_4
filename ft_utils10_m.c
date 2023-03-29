/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils10_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/29 19:13:29 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || \
	!ft_str_isdigit(col_mat[2]))
		return (-1);
	game->f_col.r = ft_atoi(col_mat[0]);
	game->f_col.g = ft_atoi(col_mat[1]);
	game->f_col.b = ft_atoi(col_mat[2]);
	game->f_col.color = create_trgb(1, game->f_col.r, game->f_col.g, \
	game->f_col.b);
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
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || \
	!ft_str_isdigit(col_mat[2]))
		return (-1);
	game->c_col.r = ft_atoi(col_mat[0]);
	game->c_col.g = ft_atoi(col_mat[1]);
	game->c_col.b = ft_atoi(col_mat[2]);
	game->c_col.color = create_trgb(1, game->c_col.r, game->c_col.g, \
	game->c_col.b);
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

void	ft_file_split2(t_game *game)
{
	game->no_tex = ft_find_str_matrix2("NO ", game->file);
	game->so_tex = ft_find_str_matrix2("SO ", game->file);
	game->we_tex = ft_find_str_matrix2("WE ", game->file);
	game->ea_tex = ft_find_str_matrix2("EA ", game->file);
}

int	ft_file_split(t_game *game)
{
	ft_file_split2(game);
	if (ft_check_tex(game) == -1)
	{
		printf("\nError with textures\n");
		return (-1);
	}
	game->col_f = ft_find_str_matrix2("F ", game->file);
	game->col_c = ft_find_str_matrix2("C ", game->file);
	if (!game->col_f || !game->col_c \
	|| (ft_get_color_c(game) == -1) || (ft_get_color_f(game) == -1))
	{
		printf("\nError with colors\n");
		return (-1);
	}
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
