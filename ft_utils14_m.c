/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils14_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/30 20:19:31 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_variables_e(t_data *m)
{
	m->dir_x = 1;
	m->dir_y = 0;
	m->plane_x = 0;
	m->plane_y = 0.66;
}

void	init_variables_w(t_data *m)
{
	m->dir_x = -1;
	m->dir_y = 0;
	m->plane_x = 0;
	m->plane_y = -0.66;
}

void	init_variables_n(t_data *m)
{
	m->dir_x = 0;
	m->dir_y = -1;
	m->plane_x = 0.66;
	m->plane_y = 0;
}

void	init_variables_s(t_data *m)
{
	m->dir_x = 0;
	m->dir_y = 1;
	m->plane_x = -0.66;
	m->plane_y = 0;
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
		init_variables_e(m);
	else if (a == 'W')
		init_variables_w(m);
	else if (a == 'N')
		init_variables_n(m);
	else if (a == 'S')
		init_variables_s(m);
	m->time = 0;
	m->old_time = 0;
	m->r_s = 25;
	m->move_speed = 0.2;
}
