/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:56:34 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 09:56:36 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		put_and_clear_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img.ptr, 0, 0);
	mlx_destroy_image(m->mlx, m->img.ptr);
    if (!m->minimap_toggle)
    {
    	put_pixel(&(m->minimap), m->pl.posX * 5, m->pl.posY * 5, WHITE);
    	mlx_put_image_to_window(m->mlx, m->win, m->minimap.ptr,
    		WIN_WIDTH - m->map.wd * 5 - 10, 10);
    	put_pixel(&(m->minimap), m->pl.posX * 5, m->pl.posY * 5, 0);
    }
    if (!m->instruction_toggle)
        print_instructions(m);
}

void		calc_texture(t_mlx *m, int side, double wall_x)
{
    int length;

    length = 64;
	if (side == 0)
		wall_x = m->pl.posY + m->pl.pWallDist * m->pl.rayDirY;
	else
		wall_x = m->pl.posX + m->pl.pWallDist * m->pl.rayDirX;
	wall_x -= floor(wall_x);
	m->texture.texX = (int)(wall_x * length);
	if (side == 0 && m->pl.rayDirX > 0)
		m->texture.texX = length - m->texture.texX - 1;
	if (side == 1 && m->pl.rayDirY < 0)
		m->texture.texX = length - m->texture.texX - 1;
}

int			perform_dda(t_mlx *m, int step_x, int step_y, int hit, int side)
{
    hit = 0;
	while (hit == 0 && m->map.x < m->map.wd - 1 && m->map.y < m->map.ht - 1)
	{
		if (m->pl.sideDistX < m->pl.sideDistY)
		{
			m->pl.sideDistX += m->pl.deltaDistX;
			m->map.x += step_x;
			side = 0;
		}
		else
		{
			m->pl.sideDistY += m->pl.deltaDistY;
			m->map.y += step_y;
			side = 1;
		}
		(m->map.grid[m->map.x][m->map.y] != 0) ? hit = 1 : 0;
	}
    if (side == 0)
        m->pl.pWallDist =
            (m->map.x - m->pl.posX + (1 - step_x) / 2) / m->pl.rayDirX;
    else
        m->pl.pWallDist =
            (m->map.y - m->pl.posY + (1 - step_y) / 2) / m->pl.rayDirY;
	calc_texture(m, side, 0.0);
	return (side);
}

int			find_wall(t_mlx *m, int step_x, int step_y)
{
	if (m->pl.rayDirX < 0)
	{
		step_x = -1;
		m->pl.sideDistX = (m->pl.posX - m->map.x) * m->pl.deltaDistX;
	}
	else
	{
		step_x = 1;
		m->pl.sideDistX = (m->map.x + 1.0 - m->pl.posX) * m->pl.deltaDistX;
	}
	if (m->pl.rayDirY < 0)
	{
		step_y = -1;
		m->pl.sideDistY = (m->pl.posY - m->map.y) * m->pl.deltaDistY;
	}
	else
	{
		step_y = 1;
		m->pl.sideDistY = (m->map.y + 1.0 - m->pl.posY) * m->pl.deltaDistY;
	}
	return (perform_dda(m, step_x, step_y, 0, 0));
}

void		raycast(t_mlx *m)
{
	int		x;
	double	camera_x;
	int		side;

	m->img.ptr = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img.str = mlx_get_data_addr(m->img.ptr, &(m->img.bpp),
			&(m->img.size_line), &(m->img.endian));
	m->img.bpp /= 8;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)(WIN_WIDTH) - 1;
		m->pl.rayDirX = m->pl.dirX + m->pl.planeX * camera_x;
		m->pl.rayDirY = m->pl.dirY + m->pl.planeY * camera_x;
		m->map.x = (int)(m->pl.posX);
		m->map.y = (int)(m->pl.posY);
		m->pl.deltaDistX = fabs(1 / m->pl.rayDirX);
		m->pl.deltaDistY = fabs(1 / m->pl.rayDirY);
        side = find_wall(m, 0, 0);
		calc_lineheight(m, side, x);
	}
	put_and_clear_img(m);
}
