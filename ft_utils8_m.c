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

char	**ft_get_map(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	int		size;
	int		check;

	i = 0;
	size = 0;
	check = 0;
	while (game->file_save[i] && game->file_save[i][0] && game->file_save[i][0] != '1')
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