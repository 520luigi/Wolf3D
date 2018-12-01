/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_loops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:11:59 by szheng            #+#    #+#             */
/*   Updated: 2018/11/29 22:12:01 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	move_rotation(t_mlx *m, double rspeed)
{
	if (m->m.r_rot)
	{
		m->p.od = m->p.dx;
		m->p.dx = m->p.dx * cos(-rspeed) - m->p.dy * sin(-rspeed);
		m->p.dy = m->p.od * sin(-rspeed) + m->p.dy * cos(-rspeed);
		m->p.opln = m->p.plnx;
		m->p.plnx = m->p.plnx * cos(-rspeed) - m->p.plny * sin(-rspeed);
		m->p.plny = m->p.opln * sin(-rspeed) + m->p.plny * cos(-rspeed);
	}
	else
	{
		m->p.od = m->p.dx;
		m->p.dx = m->p.dx * cos(rspeed) - m->p.dy * sin(rspeed);
		m->p.dy = m->p.od * sin(rspeed) + m->p.dy * cos(rspeed);
		m->p.opln = m->p.plnx;
		m->p.plnx = m->p.plnx * cos(rspeed) - m->p.plny * sin(rspeed);
		m->p.plny = m->p.opln * sin(rspeed) + m->p.plny * cos(rspeed);
	}
	if (m->m.rspeed != 0)
		m->m.rspeed = 0;
}

void	move_forward(t_mlx *m, double movespeed)
{
	if (m->m.f)
	{
		if ((m->map.grid[(int)(m->p.posx + m->p.dx)]
					[(int)(m->p.posy + m->p.dy)]) < 1)
		{
			m->p.posx += m->p.dx * movespeed;
			m->p.posy += m->p.dy * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->p.posx - m->p.dx)]
					[(int)(m->p.posy - m->p.dy)]))
		{
			m->p.posx += m->p.dx * -movespeed;
			m->p.posy += m->p.dy * -movespeed;
		}
	}
}

void	move_left(t_mlx *m, double movespeed)
{
	if (m->m.l)
	{
		if (!(m->map.grid[(int)(m->p.posx - m->p.dy)]
					[(int)(m->p.posy + m->p.dx)]))
		{
			m->p.posx -= m->p.dy * movespeed;
			m->p.posy += m->p.dx * movespeed;
		}
	}
	else
	{
		if (!(m->map.grid[(int)(m->p.posx + m->p.dy)]
					[(int)(m->p.posy - m->p.dx)]))
		{
			m->p.posx -= m->p.dy * -movespeed;
			m->p.posy += m->p.dx * -movespeed;
		}
	}
}

int		move_loop(t_mlx *m)
{
	double	movespeed;
	double	rspeed;

	movespeed = 0.00007 * WIN_WIDTH;
	rspeed = 0.00003 * WIN_WIDTH;
	if (m->m.f || m->m.b)
		move_forward(m, movespeed);
	if (m->m.l || m->m.r)
		move_left(m, movespeed);
	if (m->m.r_rot || m->m.l_rot)
		move_rotation(m, rspeed);
	if (m->m.rspeed != 0)
		move_rotation(m, m->m.rspeed);
	ft_raycaster(m);
	return (0);
}
