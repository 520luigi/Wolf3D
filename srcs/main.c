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
				put_pixel(&(m->minimap), m->pt1.y + y_inc++, m->pt1.x, WHITE);
			else if (map_value < 0)
				put_pixel(&(m->minimap), m->pt1.y + y_inc++, m->pt1.x, BLUE);
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

void        check_full_map(t_mlx *m)
{
    int cols;
    int rows;

    cols = m->map.width;
    rows = m->map.height - 1;
    while (m->map.grid[rows][--cols] != 0 && rows > 0)
    {
        if (cols <= 0)
        {
            cols = m->map.width;
            rows--;
        }
    }
    (rows < 1) ? ft_puterror("Full map error\n") : 0;
    m->pl.posX = cols;
    m->pl.posY = rows;
}

void   setup(t_mlx *m, char *filename)
{
    m->mlx = mlx_init();
    m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, filename);
    m->minimap.ptr = mlx_new_image(m->mlx, m->map.width * 5, m->map.height * 5);
	m->minimap.str = mlx_get_data_addr(m->minimap.ptr, &(m->minimap.bpp),
			&(m->minimap.size_line), &(m->minimap.endian));
	m->minimap.bpp /= 8;
    create_textures(m, 0, 0);
    m->move.detect_mouse = 1;
    m->pl.dirX = -1;
    m->pl.dirY = 0;
    m->pl.planeX = 0;
    m->pl.planeY = 0.9;
    m->minimap_toggle = 0;
    m->mouse_toggle = 0;
    check_full_map(m);
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
	mlx_hook(m.win, 2, 0, key_press, &m);
	mlx_hook(m.win, 3, 0, key_release, &m);
	mlx_hook(m.win, 6, 0, mouse_motion, &m);
	mlx_hook(m.win, 17, 0, exit_hook, 0);
	mlx_loop_hook(m.mlx, move_loop, &m);
	mlx_loop(m.mlx);
	return (0);
}
