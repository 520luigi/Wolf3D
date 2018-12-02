/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:35:06 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 09:47:20 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		draw_square(t_img *img, t_point pt1, t_point pt2, int map_value)
{
	int y;

	while (pt1.x < pt2.x)
	{
		y = 0;
		while (y < 5)
		{
			(map_value > 0) ? light_pixel(img, pt1.y + y++, pt1.x, 0x00BFFF) : 0; //positive map values on minimap color
			(map_value < 0) ? light_pixel(img, pt1.y + y++, pt1.x, 0xFF0000) : 0; //negative map values on minimap color
		}
		pt1.x++;
	}
}

void		t_point_changer(t_mlx *m, int x, int y)
{
	m->pt1.x = x * 5;
	m->pt1.y = y * 5;
    m->pt2.x = (x + 1) * 5;
	m->pt2.y = y * 5;
}

void		worldmap(t_mlx *m)
{
	int		x;
	int		y;

	y = -1;
	while (++y < m->map.height)
	{
		x = -1;
		while (++x < m->map.width)
		{
			t_point_changer(m, x, y);
			if (m->map.grid[y][x] != 0)
				draw_square(&(m->minimap), m->pt1, m->pt2, m->map.grid[y][x]);
		}
	}
}

int			main(int ac, char **av)
{
	t_mlx		m;
    int fd;

	if (ac != 2)
		ft_puterror("usage: ./wolf3d <map_name>\n");
    if ((fd = open(av[1], O_RDONLY)) < 0)
        ft_puterror("Error, no file exist\n");
	read_input(&m, av[1], fd);
	setup(&m);
	// m.mlx = mlx_init();
    // m.win = mlx_new_window(m.mlx, WIN_WIDTH, WIN_HEIGHT, av[1]);
	// m.minimap.ptr = mlx_new_image(m.mlx, m.map.width * 5, m.map.height * 5);
	// m.minimap.str = mlx_get_data_addr(m.minimap.ptr, &(m.minimap.bpp),
	// 		&(m.minimap.size_line), &(m.minimap.endian));
	// m.minimap.bpp /= 8;  //change this to 32 and others to see what's up... world map is the mini map lol, i don't think i really need this: just delete it lol...
	worldmap(&m);
	mlx_hook(m.win, 2, 0, key_press_hook, &m);
	mlx_hook(m.win, 3, 0, key_release_hook, &m); //yes same as
	mlx_hook(m.win, 6, 0, mouse_motion_hook, &m); //mouse motion of left and right as it moves....
	mlx_hook(m.win, 17, 0, exit_hook, 0); // close with an x on the window...
	mlx_loop_hook(m.mlx, move_loop, &m);
	mlx_loop(m.mlx);
	return (0);
}

//
// int		main(int ac, char **av)
// {
//     t_mlx m;
//     int fd;
//
//     if (ac != 2)
//         ft_puterror("Usage: ./wolf3d <map>\n");
//     if ((fd = open(av[1], O_RDONLY)) < 0)
//         ft_puterror("Error, no file exist\n");
//     read_input(&m, av[1], fd);
//     setup(&m);
//     print_map(&m, -1, -1, 0); ///function used to move the map...
//     mlx_mouse_hook(m.win, deal_mouse, &m)
//     mlx_key_hook(m.win, deal_key, &m);
//     mlx_loop(m.mlx);
//     return (0);
// }
