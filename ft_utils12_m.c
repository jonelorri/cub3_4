/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils12_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:16:45 by ibaines           #+#    #+#             */
/*   Updated: 2023/03/30 20:01:08 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

void	ft_mv_cam_left(t_game *g)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = g->m.dir_x;
	g->m.dir_x = g->m.dir_x * cos(-g->m.r_s) - g->m.dir_y * sin(-g->m.r_s);
	g->m.dir_y = old_dir_x * sin(-g->m.r_s) + g->m.dir_y * cos(-g->m.r_s);
	old_plane_x = g->m.plane_x;
	g->m.plane_x = g->m.plane_x * cos(-g->m.r_s) - g->m.plane_y * \
	sin(-g->m.r_s);
	g->m.plane_y = old_plane_x * sin(-g->m.r_s) + g->m.plane_y * cos(-g->m.r_s);
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, SCREENWIDTH, SCREENHEIGHT);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, &g->m.line_length, \
	&g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

void	ft_mv_cam_right(t_game *g)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = g->m.dir_x;
	g->m.dir_x = g->m.dir_x * cos(g->m.r_s) - g->m.dir_y * sin(g->m.r_s);
	g->m.dir_y = old_dir_x * sin(g->m.r_s) + g->m.dir_y * cos(g->m.r_s);
	old_plane_x = g->m.plane_x;
	g->m.plane_x = g->m.plane_x * cos(g->m.r_s) - g->m.plane_y * sin(g->m.r_s);
	g->m.plane_y = old_plane_x * sin(g->m.r_s) + g->m.plane_y * cos(g->m.r_s);
	mlx_destroy_image(g->mlx, g->m.img);
	g->m.img = mlx_new_image(g->mlx, SCREENWIDTH, SCREENHEIGHT);
	g->m.addr = mlx_get_data_addr(g->m.img, &g->m.bpp, &g->m.line_length, \
	&g->m.endian);
	ft_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->m.img, 0, 0);
}

int	key_event(int key_code, t_game *g)
{
	if (key_code == 53)
		ft_close(g);
	else if (key_code == 0x0D)
		ft_move_up(g, SCREENWIDTH, SCREENHEIGHT);
	else if (key_code == 0x01)
		ft_move_down(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 2)
		ft_move_right(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 0)
		ft_move_left(g, SCREENWIDTH, SCREENHEIGHT);
	if (key_code == 124)
		ft_mv_cam_left(g);
	if (key_code == 123)
		ft_mv_cam_right(g);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;


	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_mlx_pixel_color(t_img *tex, int x, int y)
{
	char			*dst;
	int				offset;
	unsigned int	color;

	offset = (y * tex->line_length + x * (tex->bpp / 8));
	dst = tex->addr + offset;
	color = *(unsigned int *)dst;
	return (color);
}
