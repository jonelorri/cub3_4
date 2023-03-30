/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:15:43 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/30 19:13:14 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	free_map(g);
	//system("leaks Cub3d");
	printf("AAA\n");
	exit(0);
}

int	ft_exit_error(void)
{
	//system("leaks Cub3d");
	printf("AAA\n");
	exit(0);
}

void	free_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i])
	{
		free(g->new_map[i]);
		free(g->map[i]);
		i++;
	}
	free(g->map);
	free(g->new_map);
}

void	free_map_error(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i])
	{
		free(g->map[i]);
		i++;
	}
	free(g->map);
}
