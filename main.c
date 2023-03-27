#include "cub3d.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

int	ft_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

void	ft_write_hex_c(size_t a, int w, t_game *game)
{
	char			*hex;
	char			*hex2;
	char			*start;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';
	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	start = NULL;
	if (game->c_col.init == 0)
	{
		game->c_col.init++;
		hex2[0] = hex[a];
		hex2[1] = '\0';
		game->c_col.col = ft_strjoin("0x", hex2);
	}
	else
	{
		game->c_col.col = ft_strjoin(game->c_col.col, hex2);
	}
}

void	ft_hex_c(size_t nb, int a, t_game *game)
{
	if (nb >= 0 && nb < 16)
		ft_write_hex_c(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_c(nb / 16, a, game);
		ft_write_hex_c(nb % 16, a, game);
	}
}

void	ft_color_hex_c(t_game *game)
{
	game->c_col.init = 0;
	if (game->c_col.r < 16)
		ft_hex_c(game->c_col.r, 1, game);
	else
		ft_hex_c(game->c_col.r, 0, game);
	if (game->f_col.g < 16)
		ft_hex_c(game->c_col.g, 1, game);
	else
		ft_hex_c(game->c_col.g, 0, game);
	if (game->c_col.b < 16)
		ft_hex_c(game->c_col.b, 1, game);
	else
		ft_hex_c(game->c_col.b, 0, game);
}

void	ft_write_hex_f(size_t a, int w, t_game *game)
{
	char	*hex;
	char	*hex2;
	char	*start;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';
	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	start = NULL;
	if (game->f_col.init == 0)
	{
		game->f_col.init++;
		game->f_col.col = ft_strjoin("0x", hex2);
	}
	else
	{
		game->f_col.col = ft_strjoin(game->f_col.col, hex2);
	}
}

void	ft_hex_f(size_t nb, int a, t_game *game)
{
	if (nb >= 0 && nb < 16)
		ft_write_hex_f(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_f(nb / 16, a, game);
		ft_write_hex_f(nb % 16, a, game);
	}
}

void	ft_color_hex(t_game *game)
{
	game->f_col.init = 0;
	if (game->f_col.r < 16)
		ft_hex_f(game->f_col.r, 1, game);
	else 
		ft_hex_f(game->f_col.r, 0, game);
	if (game->f_col.g < 16)
		ft_hex_f(game->f_col.g, 1, game); 
	else 
		ft_hex_f(game->f_col.g, 0, game);
	if (game->f_col.b < 16)
		ft_hex_f(game->f_col.b, 1, game);
	else 
		ft_hex_f(game->f_col.b, 0, game);
}

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	t_map_trim(char **str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		ptr = ft_strtrim(str[i], " ");
		free (str[i]);
		str[i] = ptr;
		i++;
	}
}

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
			return(ft_strstr(mat[i], str));
		i++;
	}
	return (NULL);
}

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
				return(mat[i] + j);
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

int	ft_read_file(t_game *g, char *name)
{
	int		fd;
	int		i;

	i = 0;
	g->no_check = 0;
	g->so_check = 0;
	g->ea_check = 0;
	g->we_check = 0;
	g->c_check = 0;
	g->f_check = 0;
	if (!ft_check_format(name, ".cub"))
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

void	ft_remove_end_line(t_game *game)
{
	int		i;
	int		j;
	size_t	size;
	char	*ptr;

	i = 0;
	j = 0;
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
		return(NULL);
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
	while(game->file[i])
	{
		game->file_save[i] = ft_strdup(game->file[i]);
		i++;
	}
	game->file_save[i] = NULL;
}

int	ft_get_map2(t_game *game) //comprobar que no hay mas lineas despues del mapa
{
	int	i;

	i = 0;
	ft_file_copy(game);
	t_map_trim(game->file_save);
	while (game->file_save[i] && game->file_save[i][0] && game->file_save[i][0] != '1' )
	{
		i++;
	}
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

int	ft_get_map3(t_game *game)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (game->file_save[i][0] && game->file_save[i][0] != '1')
	{
		if (ft_strstr(game->file_save[i], "NO "))
		{
			game->no_check = 1;
			n++;
		}
		if (ft_strstr(game->file_save[i], "EA "))
			game->ea_check = 1;
		if (ft_strstr(game->file_save[i], "WE "))
			game->we_check = 1;
		if (ft_strstr(game->file_save[i], "SO "))
			game->so_check = 1;
		if (ft_strstr(game->file_save[i], "F "))
			game->f_check = 1;
		if (ft_strstr(game->file_save[i], "C "))
			game->c_check = 1;
		i++;
	}
	if (game->so_check + game->ea_check + game->we_check + game->no_check + game->c_check + game->f_check != 6)
	{
		printf("Error, invalid map\n");
		return (1);
	}
	return (0);
}

int	ft_check_tex(t_game *game)
{
	if (game->no_tex)
	{
		game->no.img = mlx_xpm_file_to_image(game->mlx, game->no_tex, &game->no.w, &game->no.h);
		game->no.line_length = 0;
		game->no.bits_per_pixel = 0;
		game->no.endian = 0;
	}
	if (!game->no.img || !game->no_tex)
		return (-1);
	game->no.addr = mlx_get_data_addr(game->no.img, &game->no.bits_per_pixel, &game->no.line_length, &game->no.endian);
	if (game->so_tex)
	{
		game->so.img = mlx_xpm_file_to_image(game->mlx, game->so_tex, &game->so.w, &game->so.h);
		game->so.line_length = 0;
		game->so.bits_per_pixel = 0;
		game->so.endian = 0;
	}
	if (!game->so.img || !game->so_tex)
		return (-1);
		game->so.addr = mlx_get_data_addr(game->so.img, &game->so.bits_per_pixel, &game->so.line_length, &game->so.endian);
	if (game->we_tex)
	{
		game->we.img = mlx_xpm_file_to_image(game->mlx, game->we_tex, &game->we.w, &game->we.h);
		game->we.line_length = 0;
		game->we.bits_per_pixel = 0;
		game->we.endian = 0;
	}
	if (!game->we.img || !game->we_tex)
		return (-1);
	game->we.addr = mlx_get_data_addr(game->we.img, &game->we.bits_per_pixel, &game->we.line_length, &game->we.endian);
	if (game->ea_tex)
	{
		game->ea.img = mlx_xpm_file_to_image(game->mlx, game->ea_tex, &game->ea.w, &game->ea.h);
		game->ea.line_length = 0;
		game->ea.bits_per_pixel = 0;
		game->ea.endian = 0;
	}
	if (!game->ea.img || !game->ea_tex)
		return (-1);
	game->ea.addr = mlx_get_data_addr(game->ea.img, &game->ea.bits_per_pixel, &game->ea.line_length, &game->ea.endian);
	return (0);
}

int	ft_check_color_com(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && (int)ft_strlen(str) > i)
			if (str[i + 1] < '0' || str[i + 1] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int ft_get_color_f(t_game *game)
{
	char	**col_mat;

	if (ft_check_color_com(game->col_f))
		return (-1);
	col_mat = ft_split(game->col_f, ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->f_col.r = ft_atoi(col_mat[0]);
	game->f_col.g = ft_atoi(col_mat[1]);
	game->f_col.b = ft_atoi(col_mat[2]);
	game->f_col.color = create_trgb(1, game->f_col.r, game->f_col.g, game->f_col.b);
	free_matrix(col_mat);
	if (game->f_col.r > 255 || game->f_col.r < 0)
		return (-1);
	if (game->f_col.g > 255 || game->f_col.g < 0)
		return (-1);
	if (game->f_col.b > 255 || game->f_col.b < 0)
		return (-1);
	return (0);
}

int	ft_get_color_c(t_game *game)
{
	char	**col_mat;	

	if (ft_check_color_com(game->col_c))
		return (-1);
	col_mat = ft_split(game->col_c , ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->c_col.r = ft_atoi(col_mat[0]);
	game->c_col.g = ft_atoi(col_mat[1]);
	game->c_col.b = ft_atoi(col_mat[2]);
	game->c_col.color = create_trgb(1, game->c_col.r, game->c_col.g, game->c_col.b);
	free_matrix(col_mat);
	if (!col_mat)
		return (-1);
	if (game->c_col.r > 255 || game->c_col.r < 0)
		return (-1);
	if (game->c_col.g > 255 || game->c_col.g < 0)
		return (-1);
	if (game->c_col.b > 255 || game->c_col.b < 0)
		return (-1);
	return (0);
}



int	ft_file_split(t_game *game)
{
	int	i;

	i = 0;
	game->no_tex = ft_find_str_matrix2("NO ", game->file);
	game->so_tex = ft_find_str_matrix2("SO ", game->file);
	game->we_tex = ft_find_str_matrix2("WE ", game->file);
	game->ea_tex = ft_find_str_matrix2("EA ", game->file);
	if (ft_check_tex(game) == -1)
	{
		printf("\nError with textures\n");
		return (-1);
	}
	game->col_f = ft_find_str_matrix2("F ", game->file);
	game->col_c = ft_find_str_matrix2("C ", game->file);
	if (!game->col_f || !game->col_c ||(ft_get_color_c(game) == -1) || (ft_get_color_f(game) == -1))
	{
		printf("\nError with colors\n");
		return (-1);
	}
	ft_color_hex(game);
	ft_color_hex_c(game);
	if (ft_get_map2(game))
		return (-1);
	game->map = ft_get_map(game);//
	if (!game->map)
		return (-1);
	if (ft_get_map3(game))
		return (-1);
	game->mv = 0;
	return (0);
}

void	ft_move_up(t_game *game, int key)
{
	double	pruebaX;
	double	pruebaY;

	key = 0;
	pruebaX = game->m.posX + game->m.dirX * game->m.moveSpeed;
	pruebaY = game->m.posY + game->m.dirY * game->m.moveSpeed;
	if (game->map[(int)game->m.posY][(int)(pruebaX)] != '1')
	{
		game->m.posX = pruebaX;
	}
	if (game->map[(int)(pruebaY)][(int)(game->m.posX)] != '1')
	{
		game->m.posY = pruebaY;
	}
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_down(t_game *game, int key)
{
	double	pruebaX;
	double	pruebaY;

	pruebaX = game->m.posX - game->m.dirX * game->m.moveSpeed;
	pruebaY = game->m.posY - game->m.dirY * game->m.moveSpeed;
	key = 0;
	if (game->map[(int)game->m.posY][(int)(pruebaX)] != '1')
		game->m.posX = pruebaX;
	if (game->map[(int)(pruebaY)][(int)(game->m.posX)] != '1')
		game->m.posY = pruebaY;
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_left(t_game *game, int key)
{
	double	pruebaX;
	double	pruebaY;

	key = 0;
	pruebaX = game->m.posX + ( game->m.dirY) * game->m.moveSpeed;
	pruebaY = game->m.posY -  game->m.dirX * game->m.moveSpeed;
	if (game->map[(int)game->m.posY][(int)(pruebaX)] != '1')
		game->m.posX = pruebaX;
	if (game->map[(int)(pruebaY)][(int)(game->m.posX)] != '1')
		game->m.posY = pruebaY;
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

void	ft_move_right(t_game *game, int key)
{
	double	pruebaX;
	double	pruebaY;

	key = 0;
	pruebaX = game->m.posX - ( game->m.dirY) * game->m.moveSpeed;
	pruebaY = game->m.posY + game->m.dirX * game->m.moveSpeed;
	if (game->map[(int)(pruebaY)][(int)game->m.posX] != '1')
	{
		game->m.posY = pruebaY;
	}
	if (game->map[(int)(game->m.posY)][(int)(pruebaX)] != '1')
	{
		game->m.posX = pruebaX;
	}
	mlx_destroy_image(game->mlx, game->m.img);
	game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
	ft_draw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
}

int	key_event(int key_code, t_game *game)
{
	double	oldPlaneX;
	double	oldDirX;

	if (key_code == 53)
		exit(0);
	else if (key_code == 0x0D)
		ft_move_up(game, key_code);
	else if (key_code == 0x01)
		ft_move_down(game, key_code);
	 if (key_code == 2)
		ft_move_right(game, key_code);
	 if (key_code == 0)
		ft_move_left(game, key_code);
	if (key_code == 124)
	{
		oldDirX = game->m.dirX;
		game->m.dirX = game->m.dirX * cos(-game->m.rotSpeed) - game->m.dirY * sin(-game->m.rotSpeed);
		game->m.dirY = oldDirX * sin(-game->m.rotSpeed) + game->m.dirY * cos(-game->m.rotSpeed);
		oldPlaneX = game->m.planeX;
		game->m.planeX = game->m.planeX * cos(-game->m.rotSpeed) - game->m.planeY * sin(-game->m.rotSpeed);
		game->m.planeY = oldPlaneX * sin(-game->m.rotSpeed) + game->m.planeY * cos(-game->m.rotSpeed);
		mlx_destroy_image(game->mlx, game->m.img);
		game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
		game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
		ft_draw(game);
		mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
	}
	else if (key_code == 123)
	{
		oldDirX = game->m.dirX;
		game->m.dirX = game->m.dirX * cos(game->m.rotSpeed) - game->m.dirY * sin(game->m.rotSpeed);
		game->m.dirY = oldDirX * sin(game->m.rotSpeed) + game->m.dirY * cos(game->m.rotSpeed);
		oldPlaneX = game->m.planeX;
		game->m.planeX = game->m.planeX * cos(game->m.rotSpeed) - game->m.planeY * sin(game->m.rotSpeed);
		game->m.planeY = oldPlaneX * sin(game->m.rotSpeed) + game->m.planeY * cos(game->m.rotSpeed);
		mlx_destroy_image(game->mlx, game->m.img);
		game->m.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
		game->m.addr = mlx_get_data_addr(game->m.img, &game->m.bits_per_pixel, &game->m.lineLength, &game->m.endian);
		ft_draw(game);
		mlx_put_image_to_window(game->mlx, game->win, game->m.img, 0, 0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->lineLength + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_mlx_pixel_color(t_img *tex, int x, int y)
{
	char			*dst;
	int				offset;
	unsigned int	color;

	offset = (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	dst = tex->addr + offset;
	color = *(unsigned int *)dst;
	return (color);
}

static void	draw_column(t_game *game, int x, int y, t_img *tex)
{
	my_mlx_pixel_put(&game->m, x, y, get_mlx_pixel_color(tex, game->texX, game->texY));
}

void	ver_line(t_data *m, int x, t_game *game)
{
	int	i;

	i = 0;
	while (i < m->drawStart)
	{
		my_mlx_pixel_put(m, x, i, game->c_col.color);
		i ++;
	}
	while (i < SCREENHEIGHT)
	{
		game->texY = (int)game->texPos & (game->texHeight - 1);
		game->texPos += game->step;
		if (game->m.color == 1)
			draw_column(game, x, i, &game->no);
		if (game->m.color == 2)
			draw_column(game, x, i, &game->we);
		if (game->m.color == 3)
			draw_column(game, x, i, &game->so);
		if (game->m.color == 4)
			draw_column(game, x, i, &game->ea);
		i ++;
	}
	while (m->drawEnd < SCREENHEIGHT)
	{
		my_mlx_pixel_put(m, x, m->drawEnd, game->f_col.color);
		m->drawEnd ++;
	}
}

char	ft_find_pj(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E' || game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W')
				return (game->map[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	return ('X');
}

void	init_variables(t_data *m, t_game *game)
{
	char	a;

	a = ft_find_pj(game);
	m->posX = game->p.x + 0.5;
	m->posY = game->p.y + 0.5;
	game->texHeight = 64;
	game->texWidth = 64;
	if (a == 'E')
	{
		m->dirX = 1;
		m->dirY = 0;
		m->planeX = 0;
		m->planeY = 0.66;
	}
	else if (a == 'W')
	{
		m->dirX = -1;
		m->dirY = 0;
		m->planeX = 0;
		m->planeY = -0.66;
	}
	else if (a == 'N')
	{
		m->dirX = 0;
		m->dirY = -1;
		m->planeX = 0.66;
		m->planeY = 0;
	}
	else if (a == 'S')
	{
		m->dirX = 0;
		m->dirY = 1;
		m->planeX = -0.66;
		m->planeY = 0;
	}
	m->time = 0;
	m->oldTime = 0;
	m->rotSpeed = 25;
	m->moveSpeed = 0.1;
}

void	ft_draw(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		game->m.cameraX = 2 * x / (double)SCREENWIDTH - 1;
		game->m.rayDirX = game->m.dirX + game->m.planeX * game->m.cameraX;
		game->m.rayDirY = game->m.dirY + game->m.planeY * game->m.cameraX;
		game->m.mapX = (int)game->m.posX;
		game->m.mapY = (int)game->m.posY;
		if (game->m.rayDirX == 0)
			game->m.deltaDistX = exp(30);
		else
			game->m.deltaDistX = fabs(1.0 / game->m.rayDirX);
		if (game->m.rayDirY == 0)
			game->m.deltaDistY = exp(30);
		else
			game->m.deltaDistY = fabs(1.0 / game->m.rayDirY);
		game->m.hit = 0;
		if (game->m.rayDirX < 0)
		{
			game->m.stepX = -1;
			game->m.sideDistX = (game->m.posX - game->m.mapX) * game->m.deltaDistX;
		}
		else
		{
			game->m.stepX = 1;
			game->m.sideDistX = (game->m.mapX + 1.0 - game->m.posX) * game->m.deltaDistX;
		}
		if (game->m.rayDirY < 0)
		{
			game->m.stepY = -1;
			game->m.sideDistY = (game->m.posY - game->m.mapY) * game->m.deltaDistY;
		}
		else
		{
			game->m.stepY = 1;
			game->m.sideDistY = (game->m.mapY + 1.0 - game->m.posY) * game->m.deltaDistY;
		}
		while (game->m.hit == 0)
		{
			if (game->m.sideDistX < game->m.sideDistY)
			{
				game->m.sideDistX += game->m.deltaDistX;
				game->m.mapX += game->m.stepX;
				game->m.side = 0;
			}
			else
			{
				game->m.sideDistY += game->m.deltaDistY;
				game->m.mapY += game->m.stepY;
				game->m.side = 1;
			}
			if (game->map[game->m.mapY][game->m.mapX] == '1')
				game->m.hit = 1;
		}
		if (game->m.side == 0)
		{
			if (game->m.rayDirX > 0)
				game->m.color = 1;
			else
				game->m.color = 2;
			game->m.perpWallDist = (game->m.sideDistX - game->m.deltaDistX);
		}
		else
		{
			game->m.perpWallDist = (game->m.sideDistY - game->m.deltaDistY);
			if (game->m.rayDirY > 0)
				game->m.color = 3;
			else
				game->m.color = 4;
		}
		game->m.lineHeight = (int)(SCREENHEIGHT / game->m.perpWallDist);
		game->m.drawStart = -game->m.lineHeight / 2 + SCREENHEIGHT / 2;
		if (game->m.drawStart < 0)
			game->m.drawStart = 0;
		game->m.drawEnd = game->m.lineHeight / 2 + SCREENHEIGHT / 2;
		if (game->m.drawEnd >= SCREENHEIGHT)
			game->m.drawEnd = SCREENHEIGHT - 1;
		if (game->m.side == 0)
			game->wallx = game->m.posY + game->m.perpWallDist * game->m.rayDirY;
		else
			game->wallx = game->m.posX + game->m.perpWallDist * game->m.rayDirX;
		game->wallx -= floor(game->wallx);
		game->texX = (int)(game->wallx * (double)game->texWidth);
		if (game->m.side == 0 && game->m.rayDirX > 0)
			game->texX = game->texWidth - game->texX - 1;
		if (game->m.side == 1 && game->m.rayDirY < 0)
			game->texX = game->texWidth - game->texX - 1;
		game->step = 1.0 * game->texHeight / game->m.lineHeight;
		game->texPos = (game->m.drawStart - SCREENHEIGHT / 2 + game->m.lineHeight / 2) * game->step;
		ver_line(&game->m, x, game);
		x ++;
	}
}

void	fill_new_map(t_game *game)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	j = 0;
	while (game->map[j])
		j ++;
	game->newMap = (int **)malloc(sizeof(int *) * j);
	while (w < j)
	{
		while (game->map[w][i])
			i ++;
		game->newMap[w] = (int *)malloc(sizeof(int) * i);
		i = 0;
		while (game->map[w][i])
		{
			if (game->map[w][i] == '1')
				game->newMap[w][i] = 1;
			else
				game->newMap[w][i] = 0;
			i ++;
		}
		i = 0;
		w ++;
	}
}

int	main(int argc, char **argv)
{
	int		x;
	t_game	game;
	int		i;

	i = 0;
	if (argc < 2)
		return (0);
	if (ft_read_file(&game, argv[1]) == 0)
		return (0);
	while (i < game.mh)
		i++;
	x = 0;
	game.mlx = mlx_init();
	ft_remove_end_line(&game);
	if (ft_file_split(&game) == -1)
		return (-1);
	if (ft_map_check(&game) == -1)
		return (-1);
	init_variables(&game.m, &game);
	fill_new_map(&game);
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	game.m.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	game.m.addr = mlx_get_data_addr(game.m.img, &game.m.bits_per_pixel, &game.m.lineLength, &game.m.endian);
	ft_draw(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.m.img, 0, 0);
	mlx_hook(game.win, 2, 0, &key_event, &game);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_loop(game.mlx);
}
