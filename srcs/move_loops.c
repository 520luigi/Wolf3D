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

void	move_rotation(t_mlx *m, double r)
{
	if (m->move.right_rotation)
	{
		m->pl.oldDirX = m->pl.dirX;
		m->pl.dirX = m->pl.dirX * cos(-r) - m->pl.dirY * sin(-r);
		m->pl.dirY = m->pl.oldDirX * sin(-r) + m->pl.dirY * cos(-r);
		m->pl.oldPlaneX = m->pl.planeX;
		m->pl.planeX = m->pl.planeX * cos(-r) - m->pl.planeY * sin(-r);
		m->pl.planeY = m->pl.oldPlaneX * sin(-r) + m->pl.planeY * cos(-r);
	}
	else
	{
		m->pl.oldDirX = m->pl.dirX;
		m->pl.dirX = m->pl.dirX * cos(r) - m->pl.dirY * sin(r);
		m->pl.dirY = m->pl.oldDirX * sin(r) + m->pl.dirY * cos(r);
		m->pl.oldPlaneX = m->pl.planeX;
		m->pl.planeX = m->pl.planeX * cos(r) - m->pl.planeY * sin(r);
		m->pl.planeY = m->pl.oldPlaneX * sin(r) + m->pl.planeY * cos(r);
	}
	if (m->move.rotation_speed != 0)
		m->move.rotation_speed = 0;
}

void	move_forward(t_mlx *m, double movespeed)
{
	if (m->move.forward)
	{
		if ((m->map.grid[(int)(m->pl.posX + m->pl.dirX)]
					[(int)(m->pl.posY + m->pl.dirY)]) < 1)
		{
			m->pl.posX += m->pl.dirX * movespeed;
			m->pl.posY += m->pl.dirY * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->pl.posX - m->pl.dirX)]
					[(int)(m->pl.posY - m->pl.dirY)]))
		{
			m->pl.posX += m->pl.dirX * -movespeed;
			m->pl.posY += m->pl.dirY * -movespeed;
		}
	}
}

void	move_left(t_mlx *m, double movespeed)
{
	if (m->move.left)
	{
		if (!(m->map.grid[(int)(m->pl.posX - m->pl.dirY)]
					[(int)(m->pl.posY + m->pl.dirX)]))
		{
			m->pl.posX -= m->pl.dirY * movespeed;
			m->pl.posY += m->pl.dirX * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->pl.posX + m->pl.dirY)]
					[(int)(m->pl.posY - m->pl.dirX)]))
		{
			m->pl.posX -= m->pl.dirY * -movespeed;
			m->pl.posY += m->pl.dirX * -movespeed;
		}
	}
}

int		move_loop(t_mlx *m)
{
	double	movespeed;
	double	rotation_speed;

	movespeed = 0.00007 * WIN_WIDTH;
	rotation_speed = 0.00003 * WIN_WIDTH;
	if (m->move.forward || m->move.backward)
		move_forward(m, movespeed);
	if (m->move.left || m->move.right)
		move_left(m, movespeed);
	if (m->move.right_rotation || m->move.left_rotation)
		move_rotation(m, rotation_speed);
	if (m->move.rotation_speed != 0)
		move_rotation(m, m->move.rotation_speed);
	raycast(m);
	return (0);
}
