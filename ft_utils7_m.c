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

char	*ft_find_str_matrix2(char *str, char **mat)
{
	int	i;
	int	j;
	int	lenstr;

	i = 0;
	j = 0;
	lenstr = (int)ft_strlen(str);
	while (mat[i])
	{
		if (mat[i][j] == str[j])
		{
			j++;
			if (j == lenstr)
				return (mat[i] + j);
		}
		else
			j = 0;
		if (!j)
			i++;
	}
	return (NULL);
}

void	ft_count_lines(t_game *g, int i, int fd)
{
	char	*ptr;

	ptr = "AA";
	while (1)
	{	
		if (ptr == NULL)
			break ;
		ptr = get_next_line(fd);
		free(ptr);
		i++;
	}
	i--;
	g->mh = i;
}

void	ft_fill_map(t_game *g, int i, int fd)
{
	char	*ptr;

	ptr = "AA";
	while (1)
	{
		ptr = get_next_line(fd);
		if (ptr == NULL || i == g->mh)
			break ;
		g->mw = (int)ft_strlen(ptr);
		g->file[i] = ptr;
		i++;
	}
}

int	init_read_file(t_game *g, char *name)
{
	g->no_check = 0;
	g->so_check = 0;
	g->ea_check = 0;
	g->we_check = 0;
	g->c_check = 0;
	g->f_check = 0;
	if (!ft_check_format(name, ".cub"))
		return (0);
	return (1);
}

int	ft_read_file(t_game *g, char *name)
{
	int		fd;
	int		i;

	i = 0;
	if (init_read_file(g, name) == 0)
		return (0);
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong fd.\n");
		return (0);
	}
	else
	{
		ft_count_lines(g, i, fd);
		close (fd);
		fd = open(name, O_RDONLY);
		g->file = (char **)malloc(sizeof(char *) * (g->mh + 1));
		if (!g->file)
			return (0);
		g->file[g->mh] = NULL;
		ft_fill_map(g, i, fd);
	}
	close (fd);
	return (1);
}
