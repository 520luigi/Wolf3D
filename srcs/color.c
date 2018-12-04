/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:56:52 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 09:56:53 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		light_pixel(t_img *img, int x, int y, unsigned int color)
{
	img->str[y * img->size_line + (x * img->bpp) + 0] = color;
	img->str[y * img->size_line + (x * img->bpp) + 1] = color >> 8;
	img->str[y * img->size_line + (x * img->bpp) + 2] = color >> 16;
}

void		build_textures(t_mlx *m)
{
	int		x;
	int		y;
	int		colors[4];

	y = 0;
	while (++y <= 64)
	{
		x = 0;
		while (++x <= 64)
		{
			colors[0] = (x > 32) ? (x - 32) | y * 0x00FFFF : x | y * 0x00FFFF;
			colors[1] = (((x ^ y) % 7 * 0x0000eb) >> 1) & 0x333333;
			colors[2] = (y * 4) ^ (x * 4) * 0xFF;
			colors[3] = (((x * 0x0000FF & y * 0x0000FF)) >> 1) & 0x333333;
			m->texture.col[2][64 * (y - 1) + (x - 1)] =
				colors[0] + 0x100 * colors[0] + 0x10000 * colors[0];
			m->texture.col[3][64 * (y - 1) + (x - 1)] =
				(256 * colors[1] + 0x10000 * colors[1]);
			m->texture.col[1][64 * (y - 1) + (x - 1)] =
				colors[2] + 0x100 * colors[2] + 0x10000 * colors[2];
			m->texture.col[0][64 * (y - 1) + (x - 1)] =
				colors[3] + 0x100 * colors[3] + 0x10000 * colors[3];
		}
	}
}

void		draw(t_mlx *m, int *a, int x)
{
	int		y;
	int		color;
	int		depth;
	int		texy;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		while (y < a[1])
			light_pixel(&(m->img), x, y++, 0xDCDCC6);
		while (y >= a[1] && y < a[2])
		{
			depth = y * 256 - WIN_HEIGHT * 128 + a[0] * 128;
			texy = ((depth * 64) / a[0]) / 256;
			color = m->texture.col[a[3]][64 * texy + m->player.texx];
			light_pixel(&(m->img), x, y++, color);
		}
		light_pixel(&(m->img), x, y++, 0x04000);
	}
}

/*
** a[0] == lineheight a[1] == drawstart a[2] == drawend a[3] == texture
*/

void		find_lineheight(t_mlx *m, int side, int x)
{
	int		a[4];//make a struct for this called lineheight...

	a[0] = (int)(WIN_HEIGHT / m->player.pwalldist);
	a[1] = -a[0] / 2 + WIN_HEIGHT / 2;
	(a[1] < 0) ? a[1] = 0 : 0;
	a[2] = a[0] / 2 + WIN_HEIGHT / 2;
	(a[2] >= WIN_HEIGHT) ? a[2] = WIN_HEIGHT - 1 : 0;
	a[3] = 1;
	(side == 0 && m->player.rayDirX < 0) ? a[3] = 2 : 0;
	(side == 1 && m->player.rayDirY < 0) ? a[3] = 3 : 0;
	(side == 1 && m->player.rayDirY > 0) ? a[3] = 0 : 0;
	draw(m, a, x);
}
