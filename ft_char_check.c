/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:56:41 by ibaines           #+#    #+#             */
/*   Updated: 2023/02/07 18:31:01 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	ft_check_charac(t_game *g, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = 0;
	while (g->map[j] && j < g->mh)
	{
		while (g->map[j][i] && i < (int)ft_strlen(g->map[j]) - 1)
		{
			if (g->map[j][i] != ' ' \
					&& g->map[j][i] != 'N' && g->map[j][i] != 'S' \
					&& g->map[j][i] != 'W' && g->map[j][i] != 'E' \
					&& g->map[j][i] != '1' && g->map[j][i] != '0')
			{
				printf("\n***%c***\n", g->map[j][i]);
				return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
