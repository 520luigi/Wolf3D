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
    m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "Wolf3D");
    //initialize for storing pixels to image struct
    m->img.ptr = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    m->img.bpp = 32;
    m->img.size_line = 1 * WIDTH;
    m->img.endian = 1;
    m->img.str = mlx_get_data_addr(m->img.ptr, &(m->img.bpp),
                    &(m->img.size_line), &(m->img.endian));
}
