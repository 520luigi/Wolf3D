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

int			exit_hook(void) //ok
{
	exit(EXIT_SUCCESS);
	return (0);
}

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
	(key == W || key == UP) ? m->m.f = 1 : 0;
	(key == S || key == DOWN) ? m->m.b = 1 : 0;
	(key == A || key == LEFT) ? m->m.l = 1 : 0;
	(key == D || key == RIGHT) ? m->m.r = 1 : 0;
    (key == E) ? m->m.r_rot = 1 : 0;
	(key == Q) ? m->m.l_rot = 1 : 0;
    (key == T) ? m->toggle = !m->toggle: 0;
	(key == ESCAPE) ? exit(EXIT_SUCCESS) : 0;
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
