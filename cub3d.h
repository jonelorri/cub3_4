#ifndef LIB_H
# define LIB_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

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

void    draw_map(t_data *m, int screenWidth, int screenHeight, int **worldMap);

#endif