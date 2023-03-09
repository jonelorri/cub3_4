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

#include <stdio.h>
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
	printf("Aaaaaaaa str = %s\n", str);
	while (str[i])
	{
			printf("char *%c*\n", str[i]);
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		{
			printf("Error\nEl mapa no está cerrado\n");
			return (1);
		}
		i++;
	}
	return (0);
}

//int ft_check_car(int x, int y, )

int	ft_close_map_check(char **map, int mh) // hacer un bucle mientras el tamaño de las lineas sea el mismo
{
	int x;
	int y;
	int max_x;

	max_x = (int)ft_strlen(map[0]);
	mh = ft_malloc_dim(map);
	x = 0;
	y = 0;
	//printf("\n\n+%s+\n\n", map[0]);
	while (map[y] && y < mh)
	{
		if (y == 0)
			if (ft_close_map_top_check(map, ft_strlen(map[y])) == 1)
			return (1);
		if (y == mh -1)
			if (ft_close_map_bot_check(map, mh, ft_strlen(map[y])) == 1)
			return (1);
		while (map[y][x])
		{
			if (x != 0)
			{
				if (y < mh - 1 && x > (int)ft_strlen(map[y + 1]))
				{
					printf("AAAAAAA1\n");
					if (ft_close_map_ext(map[y] + x))
						return (1);
				}
				if (y > 0 && x > (int)ft_strlen(map[y - 1]))
					if (ft_close_map_ext(map[y] + x))
						return (1);
				if (map[y][x] == '0' && (map[y][x + 1] == ' ' || map[y][x + 1] == '\0' || map[y][x + 1] == '\n'))
				{
					printf("AAAAAAA2\n");
						return (1);
				}
				if (x < (int)ft_strlen(map[y]) && map[y][x] == ' ' && (map[y][x + 1] != '1' && map[y][x + 1] != '\n' && map[y][x + 1] != ' ' && map[y][x + 1] != '\0'))
				{
					printf("AAAAAAA3\n");
						return (1);
				}
				if (map[y][x] == ' ' && (map[y][x - 1] != '1' && map[y][x - 1] != '\n' && map[y][x - 1] != ' '))
				{
					printf("AAAAAAA4\n");
						return (1);
				}
				if (y < mh - 1 && (int)ft_strlen(map[y + 1]) >= x && (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S') && (map[y + 1][x] == ' '  || map[y + 1][x] == '\n' || map[y + 1][x] == '\0'))
				{ 
					printf("%c, compara con %c\n", map[y][x], map[y][x]);
						return (1);
				}
				if (y > 0 && (int)ft_strlen(map[y - 1]) >= x && (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S') && (map[y - 1][x] == ' '  || map[y - 1][x] == '\n' || map[y - 1][x] == '\0'))
				{
					printf("AAAAAAA6\n");
						return (1);
				}
			
			}
			if (map[y][x] == ' ' && x == 0)
			{
				//printf("a\n");
				if (x < (int)ft_strlen(map[y])  && (map[y][x + 1] != '1' && map[y][x + 1] != '\n' && map[y][x + 1] != ' ' && map[y][x + 1] != '\0'))
					return (1);
				if (y > 0 && (int)ft_strlen(map[y - 1])  && (map[y - 1][x] != ' ' && map[y - 1][x] != '1' && map[y - 1][x] != '\n' && map[y - 1][x] != '\0'))
					return (1);
				if (y < mh - 1 && (int)ft_strlen(map[y + 1]) && (map[y + 1][x] != ' ' && map[y + 1][x] != '1' && map[y + 1][x] != '\n' && map[y + 1][x] != '\0'))
					return (1);
							
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
