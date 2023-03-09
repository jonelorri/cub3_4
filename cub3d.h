#ifndef LIB_H
# define LIB_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
#include "libft/libft.h"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		lineLength;
	void	*img;
	char	**newMap;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	rotSpeed;
}				t_data;

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}	t_img;

typedef struct s_color
{
	int		init;
	int		g;
	int		b;
	int		r;
	char	*col;
}	t_color;


typedef struct s_player
{
	float	x;
	float	y;
	int		c;
    char	pos;
    int		check;
	t_img	up;
	t_img	down;
	t_img	left;
	t_img	right;

}	t_player;

typedef struct s_game
{
	t_data		m;
	void		*mlx;
	char		*print;
	int			mv;
	void		*win;
	int			u;
	int			ene;
    t_player	p;
	int			mw;
	int			mh;
	char		*col_f;
	char		*col_c;
	char		**map;
	char		**file;
	char		**file_save;
	char		**tex;
	int			no_check;
	int			so_check;
	int			we_check;
	int			ea_check;
	int			f_check;
	int			c_check;
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	char		*no_tex;
	char		*so_tex;
	char		*ea_tex;
	char		*we_tex;
	t_color		f_col;
	t_color		c_col;
}				t_game;

int     ft_map_check(t_game *g);
void	free_matrix(char **str);
int     ft_map_exit_check(t_game *g);
void	ft_map_c(char *s, t_game *g, int *c, int *e);
void	ft_map_p(char *s, t_game *g, int *p, int j);
int     ft_str_len_check(char **map, int mh);
int     ft_close_map_mid_check(char **map, int mh, int size);
int     ft_close_map_top_check(char **map, int size);
int 	ft_close_map_bot_check(char **map, int mh, int size);
int	    ft_close_map_check(char **map, int mh);
int	    ft_check_charac(t_game *g, int size);
int		ft_controlls(int keykode, t_game *g);
int		ft_close(t_game *g);

void    draw_map(t_data *m, int screenWidth, int screenHeight, int **worldMap);

#endif