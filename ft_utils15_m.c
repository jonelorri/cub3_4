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

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

int	ft_draw4(t_game *g, int x)
{
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
	g->tex_pos = (g->m.draw_start - SCREENHEIGHT / 2 + g->m.line_h / 2) \
	* g->step;
	ver_line(&g->m, x, g);
	return (x + 1);
}

int	ft_check_size(t_game *game)
{
	if (game->no.h != 64 || game->so.h != 64 \
		|| game->ea.h != 64 || game->we.h != 64)
	{
		printf("Wrong texture size\n");
		return (1);
	}
	if (game->no.w != 64 || game->so.w != 64 \
		|| game->ea.w != 64 || game->we.w != 64)
	{
		printf("Wrong texture size\n");
		return (1);
	}
	return (0);
}
