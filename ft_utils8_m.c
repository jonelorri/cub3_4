/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils8_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/29 17:59:07 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_remove_end_line(t_game *game)
{
	int		i;
	size_t	size;
	char	*ptr;

	i = 0;
	while (i < game->mh)
	{
		size = ft_strlen(game->file[i]);
		if (size > 1)
		{
			ptr = malloc(size);
			ft_strncpy(ptr, game->file[i], size - 1);
			ptr[size - 1] = '\0';
			free(game->file[i]);
			game->file[i] = ptr;
		}
		i++;
	}
}

char	**ft_get_map_2(int size, int j, t_game *game)
{
	int		i;
	char	**map;

	map = (char **)malloc(sizeof(char *) * (size + 1));
	i = j;
	size = 0;
	while (game->file[i])
	{
		map[size] = ft_strdup(game->file[i]);
		size++;
		i++;
	}
	map[size] = NULL;
	return (map);
}

char	**ft_get_map(t_game *game)
{
	int		i;
	int		j;
	int		size;
	int		check;

	i = 0;
	size = 0;
	check = 0;
	while (game->file_save[i] && game->file_save[i][0] \
		&& game->file_save[i][0] != '1')
		i++;
	j = i;
	while (game->file_save[i])
	{
		if (ft_strstr(game->file_save[i], "1"))
			check = 1;
		size++;
		i++;
	}
	if (!check)
	{
		printf("Error, invalid map\n");
		return (NULL);
	}
	return (ft_get_map_2(size, j, game));
}

void	ft_file_copy(t_game	*game)
{
	int	i;

	i = 0;
	game->file_save = (char **)malloc(sizeof(char *) * (game->mh + 1));
	if (!game->file)
		return ;
	while (game->file[i])
	{
		game->file_save[i] = ft_strdup(game->file[i]);
		i++;
	}
	game->file_save[i] = NULL;
}

int	ft_get_map2(t_game *game)
{
	int	i;

	i = 0;
	ft_file_copy(game);
	t_map_trim(game->file_save);
	while (game->file_save[i] && game->file_save[i][0] \
		&& game->file_save[i][0] != '1' )
		i++;
	while (game->file_save[i])
	{
		if (ft_strchr(game->file_save[i], '\n'))
		{
			printf("Error, invalid map\n");
			return (1);
		}
		i++;
	}
	return (0);
}
