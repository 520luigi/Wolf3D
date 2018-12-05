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

int			exit_hook(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int		mouse_motion(int x, int y, t_mlx *m)
{
	double rotation_speed;

	y += 0;
	rotation_speed = 0.007;
    if (!m->mouse_toggle)
    {
    	if (!m->move.detect_mouse)
    	{
    		rotation_speed *= abs(x - m->move.x_old);
    		if (x > m->move.x_old)
    			rotation_speed *= -1;
    		m->move.rotation_speed = rotation_speed;
    	}
    	else
    		m->move.detect_mouse = 0;
    	m->move.x_old = x;
    }
	return (0);
}

int		key_press(int key, t_mlx *m)
{
	(key == W || key == UP) ? m->move.forward = 1 : 0;
	(key == S || key == DOWN) ? m->move.backward = 1 : 0;
	(key == A || key == LEFT) ? m->move.left = 1 : 0;
	(key == D || key == RIGHT) ? m->move.right = 1 : 0;
    (key == E) ? m->move.right_rotation = 1 : 0;
	(key == Q) ? m->move.left_rotation = 1 : 0;
    (key == T) ? m->minimap_toggle = !m->minimap_toggle: 0;
    (key == Y) ? m->mouse_toggle = !m ->mouse_toggle: 0;
	(key == ESCAPE) ? exit(EXIT_SUCCESS) : 0;
	return (0);
}

int		key_release(int key, t_mlx *m)
{
	(key == W || key == UP) ? m->move.forward = 0 : 0;
	(key == S || key == DOWN) ? m->move.backward = 0 : 0;
	(key == A || key == LEFT) ? m->move.left = 0 : 0;
	(key == D || key == RIGHT) ? m->move.right = 0 : 0;
	(key == E) ? m->move.right_rotation = 0 : 0;
	(key == Q) ? m->move.left_rotation = 0 : 0;
	return (0);
}
