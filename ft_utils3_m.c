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

int	first3_map_check(char **map, int mh, int x, int y)
{
	if (y < mh - 1 && (int)ft_strlen(map[y + 1]) >= x && (map[y][x] == '0' \
	|| map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || \
	map[y][x] == 'S') && (map[y + 1][x] == ' ' || map[y + 1][x] == '\n' || \
	map[y + 1][x] == '\0'))
		return (1);
	if (y > 0 && (int)ft_strlen(map[y - 1]) >= x && (map[y][x] == '0' || \
	map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] \
	== 'S') && (map[y - 1][x] == ' ' || map[y - 1][x] == '\n' || \
	map[y - 1][x] == '\0'))
		return (1);
	return (0);
}

int	first_map_check(char **map, int mh, int x, int y)
{
	if (x != 0)
	{
		if (first2_map_check(map, mh, x, y) == 1)
			return (1);
		if (y > 0 && x > (int)ft_strlen(map[y - 1]))
			if (ft_close_map_ext(map[y] + x))
				return (1);
		if (map[y][x] == '0' && (map[y][x + 1] == ' ' || \
			map[y][x + 1] == '\0' || map[y][x + 1] == '\n'))
			return (1);
		if (x < (int)ft_strlen(map[y]) && map[y][x] == ' ' && (map[y][x + 1] != \
		'1' && map[y][x + 1] != '\n' && map[y][x + 1] != ' ' && map[y][x + 1] \
		!= '\0'))
			return (1);
		if (map[y][x] == ' ' && (map[y][x - 1] != '1' && map[y][x - 1] != '\n' \
		&& map[y][x - 1] != ' '))
			return (1);
		if (first3_map_check(map, mh, x, y) == 1)
			return (1);
	}
	return (0);
}

int	second_map_check(char **map, int mh, int x, int y)
{
	if (map[y][x] == ' ' && x == 0)
	{
		if (x < (int)ft_strlen(map[y]) && (map[y][x + 1] != '1' && \
		map[y][x + 1] != '\n' && map[y][x + 1] != ' ' && map[y][x + 1] != '\0'))
			return (1);
		if (y > 0 && (int)ft_strlen(map[y - 1]) && (map[y - 1][x] != ' ' && \
		map[y - 1][x] != '1' && map[y - 1][x] != '\n' && map[y - 1][x] != '\0'))
			return (1);
		if (y < mh - 1 && (int)ft_strlen(map[y + 1]) && (map[y + 1][x] != ' ' \
		&& map[y + 1][x] != '1' && map[y + 1][x] != '\n' && map[y + 1][x] \
		!= '\0'))
			return (1);
	}
	return (0);
}

int	both_map_check(char **map, int mh, int y)
{
	if (y == 0)
		if (ft_close_map_top_check(map, ft_strlen(map[y])) == 1)
			return (1);
	if (y == mh -1)
		if (ft_close_map_bot_check(map, mh, ft_strlen(map[y])) == 1)
			return (1);
	return (0);
}

int	ft_close_map_check(char **map, int mh)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mh = ft_malloc_dim(map);
	while (map[y] && y < mh)
	{
		if (both_map_check(map, mh, y) == 1)
			return (1);
		while (map[y][x])
		{
			if (first_map_check(map, mh, x, y) == 1)
				return (1);
			if (second_map_check(map, mh, x, y) == 1)
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
