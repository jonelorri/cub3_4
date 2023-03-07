#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int	worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->lineLength + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	verLine(t_data *m, int x)
{
	while (m->drawStart < m->drawEnd)
	{
		my_mlx_pixel_put(m, x, m->drawStart, 0xFF0000);
		m->drawStart += 1;
	}
}

void	init_variables(t_data *m)
{
	m->posX = 22;
	m->posY = 12;
	m->dirX = -1;
	m->dirY = 0;
	m->planeX = 0;
	m->planeY = 0.66;
	m->time = 0;
	m->oldTime = 0;
	m->hit = 0;
}

int	main()
{
	int x;
	t_data	m;

	x = 0;
	init_variables(&m);
	m.mlx = mlx_init();
	m.mlx_win = mlx_new_window(m.mlx, screenWidth, screenHeight, "Raycaster");
	m.img = mlx_new_image(m.mlx, screenWidth, screenHeight);
	m.addr = mlx_get_data_addr(m.img, &m.bits_per_pixel, &m.lineLength, &m.endian);

	//* BLUCLE PRINCIPAL
	while (x < screenWidth)
	{
		m.cameraX = 2 * x / (double)screenWidth - 1;
		m.rayDirX = m.dirX + m.planeX * m.cameraX;
		m.rayDirY = m.dirY + m.planeY * m.cameraX;
		m.mapX = (int)m.posX;
		m.mapY = (int)m.posY;
		if (m.rayDirX == 0)
			m.deltaDistX = exp(30);
		else
			m.deltaDistX = fabs(1.0 / m.rayDirX);
		if (m.rayDirY == 0)
			m.deltaDistY = exp(30);
		else
			m.deltaDistY = fabs(1.0 / m.rayDirY);
		if (m.rayDirX < 0)
		{
			m.stepX = -1;
			m.sideDistX = (m.posX - m.mapX) * m.deltaDistX;
		}
		else
		{
			m.stepX = 1;
			m.sideDistX = (m.mapX + 1.0 - m.posX) * m.deltaDistX;
		}
		if (m.rayDirY < 0)
		{
			m.stepY = -1;
			m.sideDistY = (m.posY - m.mapY) * m.deltaDistY;
		}
		else
		{
			m.stepY = 1;
			m.sideDistY = (m.mapY + 1.0 - m.posY) * m.deltaDistY;
		}
		//// perform DDA
		while (m.hit == 0)
		{
			if (m.sideDistX < m.sideDistY)
			{
				m.sideDistX += m.deltaDistX;
				m.mapX += m.stepX;
				m.side = 0;
			}
			else
			{
				m.sideDistY += m.deltaDistY;
				m.mapY += m.stepY;
				m.side = 1;
			}
			if (worldMap[m.mapY][m.mapX] > 0)
				m.hit = 1;
			// if (worldMap[m.mapX][m.mapY] > 0)
			// 	m.hit = 1;
		}
		if (m.side == 0)
			m.perpWallDist = (m.sideDistX - m.deltaDistX);
		else
			m.perpWallDist = (m.sideDistY - m.deltaDistY);
		m.lineHeight = (int)(screenHeight / m.perpWallDist);
		m.drawStart = -m.lineHeight / 2 + screenHeight / 2;
		if(m.drawStart < 0)
			m.drawStart = 0;
		m.drawEnd = m.lineHeight / 2 + screenHeight / 2;
		if(m.drawEnd >= screenHeight)
			m.drawEnd = screenHeight - 1;
		m.color = 0x0000FF;
		// if (m.side == 1)
		// 	m.color = m.color / 2;
		verLine(&m, x);
		mlx_put_image_to_window(m.mlx, m.mlx_win, m.img, 0, 0);
		x ++;
	}
	mlx_loop(m.mlx);
}