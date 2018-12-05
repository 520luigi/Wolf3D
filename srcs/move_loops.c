/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_loops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:11:59 by szheng            #+#    #+#             */
/*   Updated: 2018/11/29 22:12:01 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	move_forward_backward(t_mlx *m, double ms)
{
	if (m->move.forward)
	{
		if ((m->map.grid[(int)(m->pl.posX + m->pl.dirX)]
					[(int)(m->pl.posY + m->pl.dirY)]) < 1)
		{
			m->pl.posX += m->pl.dirX * ms;
			m->pl.posY += m->pl.dirY * ms;
		}
	}
	else if (m->move.backward)
	{
		if (!(m->map.grid[(int)(m->pl.posX - m->pl.dirX)]
					[(int)(m->pl.posY - m->pl.dirY)]))
		{
			m->pl.posX -= m->pl.dirX * ms;
			m->pl.posY -= m->pl.dirY * ms;
		}
	}
}

void	move_left_right(t_mlx *m, double ms)
{
	if (m->move.left)
	{
		if (!(m->map.grid[(int)(m->pl.posX - m->pl.dirY)]
					[(int)(m->pl.posY + m->pl.dirX)]))
		{
			m->pl.posX -= m->pl.dirY * ms;
			m->pl.posY += m->pl.dirX * ms;
		}
	}
	else if (m->move.right)
	{
		if (!(m->map.grid[(int)(m->pl.posX + m->pl.dirY)]
					[(int)(m->pl.posY - m->pl.dirX)]))
		{
			m->pl.posX += m->pl.dirY * ms;
			m->pl.posY -= m->pl.dirX * ms;
		}
	}
}

void	move_rotation(t_mlx *m, double rs)
{
	if (m->move.right_rotation)
	{
		m->pl.oldDirX = m->pl.dirX;
		m->pl.dirX = m->pl.dirX * cos(rs) + m->pl.dirY * sin(rs);
		m->pl.dirY = m->pl.dirY * cos(rs) - m->pl.oldDirX * sin(rs);
		m->pl.oldPlaneX = m->pl.planeX;
		m->pl.planeX = m->pl.planeX * cos(rs) + m->pl.planeY * sin(rs);
		m->pl.planeY = m->pl.planeY * cos(rs) - m->pl.oldPlaneX * sin(rs);
	}
	else
	{
		m->pl.oldDirX = m->pl.dirX;
		m->pl.dirX = m->pl.dirX * cos(rs) - m->pl.dirY * sin(rs);
		m->pl.dirY = m->pl.oldDirX * sin(rs) + m->pl.dirY * cos(rs);
		m->pl.oldPlaneX = m->pl.planeX;
		m->pl.planeX = m->pl.planeX * cos(rs) - m->pl.planeY * sin(rs);
		m->pl.planeY = m->pl.oldPlaneX * sin(rs) + m->pl.planeY * cos(rs);
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
