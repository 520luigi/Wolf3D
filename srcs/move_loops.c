/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_loops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:11:59 by szheng            #+#    #+#             */
/*   Updated: 2018/12/05 12:16:51 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	move_forward_backward(t_mlx *m, double ms)
{
	if (m->move.forward)
	{
		if ((m->map.grid[(int)(m->pl.pos_x + m->pl.dir_x)]
					[(int)(m->pl.pos_y + m->pl.dir_y)]) < 1)
		{
			m->pl.pos_x += m->pl.dir_x * ms;
			m->pl.pos_y += m->pl.dir_y * ms;
		}
	}
	else if (m->move.backward)
	{
		if (!(m->map.grid[(int)(m->pl.pos_x - m->pl.dir_x)]
					[(int)(m->pl.pos_y - m->pl.dir_y)]))
		{
			m->pl.pos_x -= m->pl.dir_x * ms;
			m->pl.pos_y -= m->pl.dir_y * ms;
		}
	}
}

void	move_left_right(t_mlx *m, double ms)
{
	if (m->move.left)
	{
		if (!(m->map.grid[(int)(m->pl.pos_x - m->pl.dir_y)]
					[(int)(m->pl.pos_y + m->pl.dir_x)]))
		{
			m->pl.pos_x -= m->pl.dir_y * ms;
			m->pl.pos_y += m->pl.dir_x * ms;
		}
	}
	else if (m->move.right)
	{
		if (!(m->map.grid[(int)(m->pl.pos_x + m->pl.dir_y)]
					[(int)(m->pl.pos_y - m->pl.dir_x)]))
		{
			m->pl.pos_x += m->pl.dir_y * ms;
			m->pl.pos_y -= m->pl.dir_x * ms;
		}
	}
}

void	move_rotation(t_mlx *m, double rs)
{
	if (m->move.right_rotation)
	{
		m->pl.old_dir_x = m->pl.dir_x;
		m->pl.dir_x = m->pl.dir_x * cos(rs) + m->pl.dir_y * sin(rs);
		m->pl.dir_y = m->pl.dir_y * cos(rs) - m->pl.old_dir_x * sin(rs);
		m->pl.old_plane_x = m->pl.plane_x;
		m->pl.plane_x = m->pl.plane_x * cos(rs) + m->pl.plane_y * sin(rs);
		m->pl.plane_y = m->pl.plane_y * cos(rs) - m->pl.old_plane_x * sin(rs);
	}
	else
	{
		m->pl.old_dir_x = m->pl.dir_x;
		m->pl.dir_x = m->pl.dir_x * cos(rs) - m->pl.dir_y * sin(rs);
		m->pl.dir_y = m->pl.old_dir_x * sin(rs) + m->pl.dir_y * cos(rs);
		m->pl.old_plane_x = m->pl.plane_x;
		m->pl.plane_x = m->pl.plane_x * cos(rs) - m->pl.plane_y * sin(rs);
		m->pl.plane_y = m->pl.old_plane_x * sin(rs) + m->pl.plane_y * cos(rs);
	}
	if (m->move.rotation_speed != 0)
		m->move.rotation_speed = 0;
}

int		movement_loop(t_mlx *m)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.00007 * WIN_WIDTH;
	rotation_speed = move_speed / 2.0;
	if (m->move.forward || m->move.backward)
		move_forward_backward(m, move_speed);
	if (m->move.left || m->move.right)
		move_left_right(m, move_speed);
	if (m->move.right_rotation || m->move.left_rotation)
		move_rotation(m, rotation_speed);
	if (m->move.rotation_speed != 0)
		move_rotation(m, m->move.rotation_speed);
	raycast(m);
	return (0);
}
