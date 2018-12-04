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

void	move_rotation(t_mlx *m, double r_speed)
{
	if (m->move.right_rotation)
	{
		m->player.od = m->player.dx;
		m->player.dx = m->player.dx * cos(-r_speed) - m->player.dy * sin(-r_speed);
		m->player.dy = m->player.od * sin(-r_speed) + m->player.dy * cos(-r_speed);
		m->player.opln = m->player.plnx;
		m->player.plnx = m->player.plnx * cos(-r_speed) - m->player.plny * sin(-r_speed);
		m->player.plny = m->player.opln * sin(-r_speed) + m->player.plny * cos(-r_speed);
	}
	else
	{
		m->player.od = m->player.dx;
		m->player.dx = m->player.dx * cos(r_speed) - m->player.dy * sin(r_speed);
		m->player.dy = m->player.od * sin(r_speed) + m->player.dy * cos(r_speed);
		m->player.opln = m->player.plnx;
		m->player.plnx = m->player.plnx * cos(r_speed) - m->player.plny * sin(r_speed);
		m->player.plny = m->player.opln * sin(r_speed) + m->player.plny * cos(r_speed);
	}
	if (m->move.rotation_speed != 0)
		m->move.rotation_speed = 0;
}

void	move_forward(t_mlx *m, double movespeed)
{
	if (m->move.forward)
	{
		if ((m->map.grid[(int)(m->player.posx + m->player.dx)]
					[(int)(m->player.posy + m->player.dy)]) < 1)
		{
			m->player.posx += m->player.dx * movespeed;
			m->player.posy += m->player.dy * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->player.posx - m->player.dx)]
					[(int)(m->player.posy - m->player.dy)]))
		{
			m->player.posx += m->player.dx * -movespeed;
			m->player.posy += m->player.dy * -movespeed;
		}
	}
}

void	move_left(t_mlx *m, double movespeed)
{
	if (m->move.left)
	{
		if (!(m->map.grid[(int)(m->player.posx - m->player.dy)]
					[(int)(m->player.posy + m->player.dx)]))
		{
			m->player.posx -= m->player.dy * movespeed;
			m->player.posy += m->player.dx * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->player.posx + m->player.dy)]
					[(int)(m->player.posy - m->player.dx)]))
		{
			m->player.posx -= m->player.dy * -movespeed;
			m->player.posy += m->player.dx * -movespeed;
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
	ft_raycaster(m);
	return (0);
}
