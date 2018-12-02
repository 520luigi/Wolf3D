/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:03:03 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 10:03:04 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void   setup(t_mlx *m)
{
    m->mlx = mlx_init();
    m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3D");

    //initialize for storing minimap image
    m->minimap.ptr = mlx_new_image(m->mlx, m->map.width * 5, m->map.height * 5);
	m->minimap.str = mlx_get_data_addr(m->minimap.ptr, &(m->minimap.bpp),
			&(m->minimap.size_line), &(m->minimap.endian));
	m->minimap.bpp /= 8;
    //initialize for storing pixels to image struct
    // m->img.ptr = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    // m->img.bpp = 32;
    // m->img.size_line = 1 * WIDTH;
    // m->img.endian = 1;
    // m->img.str = mlx_get_data_addr(m->img.ptr, &(m->img.bpp),
    //                 &(m->img.size_line), &(m->img.endian));

    int		a;
    int		b;

    build_textures(m);
    m->m.first_mouse_movement = 1;
    m->p.dx = -1;
    m->p.plny = 0.9;
    m->toggle = 0;
    a = m->map.width;
    b = m->map.height - 1;
    //this checks for full map, so that players need to be on it. add this to setup portion of the map...
    while (m->map.grid[b][--a] != 0 && b > 0)
    {
        if (a <= 0)
        {
            a = m->map.width;
            b--;
        }
    }
    (b < 1) ? ft_puterror("Full map error\n") : 0;
    m->p.posx = a;
    m->p.posy = b;
}
