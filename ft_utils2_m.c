/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:27 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/10 19:22:24 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_str_len_check(char **map, int mh)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(map[j]);
	while (map[j] && (int)j < mh)
	{
		if (i != ft_strlen(map[j]))
		{
			printf("Error\nEl mapa no es un rectángulo\n");
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_map_p(char *s, t_game *g, int *p, int j)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			printf("cantidad de jugadores = %d\n", *p);
			printf("%d, %d, \n",i, j);
			g->p.x = i;
			g->p.y = j;
			g->p.check = 1;
			g->p.pos = s[i];
			*p = *p + 1;
		}
		i++;
	}
}

int	ft_map_exit_check(t_game *g)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	j = 0;
	p = 0;
	while (g->map[j] && j < g->mh)
	{
		ft_map_p(g->map[j], g, &p, j);
		j++;
	}
	if (p == 1)
	{
		g->p.c = 0;
		return (0);
	}
	else
		return (1);
}

int	ft_map_check(t_game *g)
{
	int	size;

	size = (int)ft_strlen(g->map[0]);
	if (ft_close_map_check(g->map, g->mh) == 1)
	{ 
		printf("Error not close\n");
		return (-1);
	}
	if (ft_map_exit_check(g) == 1)
	{
		printf("Error\nFalta un Coleccionable/Salida/personaje");
		return (-1);
	}
	if (ft_check_charac(g, size) == 1)
	{
		printf("Error\nCaracter incorrecto");
		return (-1);
	}
	else
		return (0);
}
