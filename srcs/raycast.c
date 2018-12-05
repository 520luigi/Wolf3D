/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:56:34 by szheng            #+#    #+#             */
/*   Updated: 2018/12/05 12:42:34 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		put_and_clear_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img.ptr, 0, 0);
	mlx_destroy_image(m->mlx, m->img.ptr);
	if (!m->minimap_toggle)
	{
		put_pixel(&(m->minimap), m->pl.pos_x * 5, m->pl.pos_y * 5, WHITE);
		mlx_put_image_to_window(m->mlx, m->win, m->minimap.ptr,
				WIN_WIDTH - m->map.wd * 5 - 10, 10);
		put_pixel(&(m->minimap), m->pl.pos_x * 5, m->pl.pos_y * 5, 0);
	}
	if (!m->instruction_toggle)
		print_instructions(m);
}

void		calc_texture(t_mlx *m, int side, double wall_x)
{
	int length;

	length = 64;
	if (side == 0)
		wall_x = m->pl.pos_y + m->pl.perp_wall_dist * m->pl.raydir_y;
	else
		wall_x = m->pl.pos_x + m->pl.perp_wall_dist * m->pl.raydir_x;
	wall_x -= floor(wall_x);
	m->texture.texx = (int)(wall_x * length);
	if (side == 0 && m->pl.raydir_x > 0)
		m->texture.texx = length - m->texture.texx - 1;
	if (side == 1 && m->pl.raydir_y < 0)
		m->texture.texx = length - m->texture.texx - 1;
}

int			perform_dda(t_mlx *m, int step_x, int step_y, int side)
{
	int hit;

	hit = 0;
	while (hit == 0 && m->map.x < m->map.wd - 1 && m->map.y < m->map.ht - 1)
	{
		if (m->pl.side_dist_x < m->pl.side_dist_y)
		{
			m->pl.side_dist_x += m->pl.delta_dist_x;
			m->map.x += step_x;
			side = 0;
		}
		else
		{
			m->pl.side_dist_y += m->pl.delta_dist_y;
			m->map.y += step_y;
			side = 1;
		}
		(m->map.grid[m->map.x][m->map.y] != 0) ? hit = 1 : 0;
	}
	m->pl.perp_wall_dist = (side == 0) ?
		(m->map.x - m->pl.pos_x + (1 - step_x) / 2) / m->pl.raydir_x :
		(m->map.y - m->pl.pos_y + (1 - step_y) / 2) / m->pl.raydir_y;
	calc_texture(m, side, 0.0);
	return (side);
}

int			find_wall(t_mlx *m, int step_x, int step_y)
{
	if (m->pl.raydir_x < 0)
	{
		step_x = -1;
		m->pl.side_dist_x = (m->pl.pos_x - m->map.x) * m->pl.delta_dist_x;
	}
	else
	{
		step_x = 1;
		m->pl.side_dist_x = (m->map.x + 1.0 - m->pl.pos_x) * m->pl.delta_dist_x;
	}
	if (m->pl.raydir_y < 0)
	{
		step_y = -1;
		m->pl.side_dist_y = (m->pl.pos_y - m->map.y) * m->pl.delta_dist_y;
	}
	else
	{
		step_y = 1;
		m->pl.side_dist_y = (m->map.y + 1.0 - m->pl.pos_y) * m->pl.delta_dist_y;
	}
	return (perform_dda(m, step_x, step_y, 0));
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
		m->pl.raydir_x = m->pl.dir_x + m->pl.plane_x * camera_x;
		m->pl.raydir_y = m->pl.dir_y + m->pl.plane_y * camera_x;
		m->map.x = (int)(m->pl.pos_x);
		m->map.y = (int)(m->pl.pos_y);
		m->pl.delta_dist_x = fabs(1 / m->pl.raydir_x);
		m->pl.delta_dist_y = fabs(1 / m->pl.raydir_y);
		side = find_wall(m, 0, 0);
		calc_lineheight(m, side, x);
	}
	put_and_clear_img(m);
}
