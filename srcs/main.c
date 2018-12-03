/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:35:06 by szheng            #+#    #+#             */
/*   Updated: 2018/12/03 11:29:44 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		draw_minimap(t_mlx *m, int map_value)
{
	int y_inc;

	while (m->pt1.x < m->pt2.x)
	{
		y_inc = 0;
		while (y_inc < 5)
		{
			if (map_value > 0)
				light_pixel(&(m->minimap), m->pt1.x, m->pt1.y + y_inc++, BLUE);
			else if (map_value < 0)
				light_pixel(&(m->minimap), m->pt1.x, m->pt1.y + y_inc++, RED);
		}
		(m->pt1.x)++;
	}
}

void		minimap(t_mlx *m)
{
	int		col;
	int		row;

	row = -1;
	while (++row < m->map.height)
	{
		col = -1;
		while (++col < m->map.width)
		{
			m->pt1.x = col * 5;
			m->pt1.y = row * 5;
			m->pt2.x = (col + 1) * 5;
			m->pt2.y = row * 5;
			if (m->map.grid[row][col] != 0)
				draw_minimap(m, m->map.grid[row][col]);
		}
	}
}

int			main(int ac, char **av)
{
	t_mlx	m;
	int		fd;

	if (ac != 2)
		ft_puterror("usage: ./wolf3d <map_name>\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_puterror("Error, no file exist\n");
	read_input(&m, av[1], fd);
	setup(&m, av[1]);
	minimap(&m);
	mlx_hook(m.win, 2, 0, key_press_hook, &m);
	mlx_hook(m.win, 3, 0, key_release_hook, &m);
	mlx_hook(m.win, 6, 0, mouse_motion_hook, &m);
	mlx_hook(m.win, 17, 0, exit_hook, 0);
	mlx_loop_hook(m.mlx, move_loop, &m);
	mlx_loop(m.mlx);
	return (0);
}
