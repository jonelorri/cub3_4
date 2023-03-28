/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:39 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/11 12:27:00 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_controlls(int keykode, t_game *g)
{
	if (keykode == 0x35)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	else if (keykode == 0x0D)
		ft_move_up(g, keykode);
	else if (keykode == 0x00)
		ft_move_left(g, keykode);
	else if (keykode == 0x01)
		ft_move_down(g, keykode);
	else if (keykode == 0x02)
		ft_move_right(g, keykode);
	system("clear");
	printf("mv = %d\n", g->mv);
	return (0);
}
