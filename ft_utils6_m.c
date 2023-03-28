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

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_matrix_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_check_format(char *str, char *to_find)
{
	int	a;
	int	b;

	b = 0;
	a = 0;
	if (ft_strlen(to_find) == 0)
		return (str);
	while (str[a])
	{
		if (str[a + b] == to_find[b])
		{
			while (to_find[b])
			{
				b++;
				if (str[a + b] != to_find[b])
					break ;
			}
			if (b == (int)ft_strlen(to_find))
				return (str + a);
			b = 0;
		}
		a++;
	}
	printf("Error\nInvalid file, use *.cub\n");
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

char	*ft_find_str_matrix(char *str, char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		if (ft_strstr(mat[i], str))
			return (ft_strstr(mat[i], str));
		i++;
	}
	return (NULL);
}
