/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:11:50 by szheng            #+#    #+#             */
/*   Updated: 2018/11/29 22:11:51 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		mouse_motion_hook(int x, int y, t_mlx *m) //mouse tracking function
{
	double rspeed;

	y += 0;
	rspeed = 0.008;
	if (!m->m.first_mouse_movement)
	{
		rspeed *= abs(x - m->m.x_old);
		if (x > m->m.x_old)
			rspeed *= -1;
		m->m.rspeed = rspeed;
	}
	else
		m->m.first_mouse_movement = 0;
	m->m.x_old = x;
	return (0);
}

int		key_press_hook(int key, t_mlx *m)
{
	(key == 14) ? m->m.r_rot = 1 : 0;
	(key == 12) ? m->m.l_rot = 1 : 0;
	(key == 13 || key == 126) ? m->m.f = 1 : 0;
	(key == 1 || key == 125) ? m->m.b = 1 : 0;
	(key == 0 || key == 123) ? m->m.l = 1 : 0;
	(key == 2 || key == 124) ? m->m.r = 1 : 0;
	if (key == 53)
	{
		mlx_destroy_image(m->mlx, m->minimap.ptr);
		mlx_destroy_window(m->mlx, m->win);
		exit(EXIT_SUCCESS);
	}
	if (key == 8)
	{
		m->p.dx = -1;
		m->p.dy = 0;
		m->p.plnx = 0;
		m->p.plny = 0.9;
	}
	return (0);
}

int		key_release_hook(int key, t_mlx *m)
{
	if (key == 13 || key == 126)
		m->m.f = 0;
	else if (key == 1 || key == 125)
		m->m.b = 0;
	else if (key == 0 || key == 123)
		m->m.l = 0;
	else if (key == 2 || key == 124)
		m->m.r = 0;
	else if (key == 14)
		m->m.r_rot = 0;
	else if (key == 12)
		m->m.l_rot = 0;
	return (0);
}
