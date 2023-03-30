/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils13_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/30 20:47:37 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

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
	while (i < m->draw_end)
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
	while ( i < SCREENHEIGHT)
		my_mlx_pixel_put(m, x, i++, g->f_col.color);
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
			if (g->map[i][j] == 'E' || g->map[i][j] == 'N' || \
			g->map[i][j] == 'S' || g->map[i][j] == 'W')
				return (g->map[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	return ('X');
}

void	fill_new_map2(t_game *game, int w, int i)
{
	if (game->map[w][i] == '1')
		game->new_map[w][i] = 1;
	else
		game->new_map[w][i] = 0;
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
			fill_new_map2(game, w, i);
			i ++;
		}
		i = 0;
		w ++;
	}
}
