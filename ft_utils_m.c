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

int	ft_malloc_dim(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_close_map_mid_check(char **map, int mh, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j] && j < mh)
	{
		while (map[j][i])
		{
			if ((map[j][0] != '1') || (map[j][size - 2] != '1'))
			{
				printf("Error\nEl mapa no está cerrado\n");
				return (1);
			}
			if (map[j][i])
				i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	ft_close_map_top_check(char **map, int size)
{
	int	i;

	i = 0;
	while (map[0][i] && i < size - 1)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
		{
			printf("Error\nEl mapa no está cerrado\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_close_map_bot_check(char **map, int mh, int size)
{
	int	i;

	i = 0;
	while (map[mh - 1][i] && i < size - 1)
	{
		if (map[mh - 1][i] != '1' && map[mh - 1][i] != ' ')
		{
			printf("Error\nEl mapa no está cerrado\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_close_map_ext(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		{
			printf("Error\nEl mapa no está cerrado\n");
			return (1);
		}
		i++;
	}
	return (0);
}
