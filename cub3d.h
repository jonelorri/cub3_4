#ifndef LIB_H
# define LIB_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx/mlx.h"
# include <math.h>
#include "libft/libft.h"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	void	*img;
	char	**new_map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	double	camera_x;
	double	rayDir_x;
	double	rayDir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		color;
	double	rot_speed;
	double	move_speed;
}				t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_color
{
	int		color;
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
	int			**newMap;
	int			texNum;
	int			texX;
	int			texY;
	int			texWidth;
	int			texHeight;
	double		texPos;
	double		step;
	char		**file;
	double		wallx;
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

void	ft_draw(t_game *game);
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

#endif