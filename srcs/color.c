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

void	print_instructions(t_mlx *m)
{
	mlx_string_put(m->mlx, m->win, 8, 0, WHITE,
		"Toggle Instructions > i");
	mlx_string_put(m->mlx, m->win, 8, 15, WHITE,
        "Toggle Mouse Rotation > y");
	mlx_string_put(m->mlx, m->win, 8, 30, WHITE,
		"Toggle Minimap > t");
	mlx_string_put(m->mlx, m->win, 8, 45, WHITE,
		"Move > WASD or Arrow Keys");
	mlx_string_put(m->mlx, m->win, 8, 60, WHITE,
        "Rotation > Q E");
	mlx_string_put(m->mlx, m->win, 8, 75, WHITE,
        "Quit > ESC");
}

void		put_pixel(t_img *img, int x, int y, unsigned int color)
{
	img->str[y * img->size_line + (x * img->bpp) + 0] = color;
	img->str[y * img->size_line + (x * img->bpp) + 1] = color >> 8;
	img->str[y * img->size_line + (x * img->bpp) + 2] = color >> 16;
}

void		create_textures(t_mlx *m, int x, int y)
{
	int		colors[3];
    int     length;

	y = 0;
    length = 64;
	while (++y <= length)
	{
		x = 0;
		while (++x <= length)
		{
            colors[0] = 0xc00000;
			colors[1] = 0x778899;
            colors[2] = (y * 4) ^ (x * 4) * 0xFF;
            m->texture.pat[0][length * (y - 1) + (x - 1)] =
				colors[0] * (x % 16 && y % 16);
			m->texture.pat[1][length * (y - 1) + (x - 1)] =
				colors[1] * (x % 16 && y % 16);
			m->texture.pat[2][length * (y - 1) + (x - 1)] =
                colors[2];
			m->texture.pat[3][length * (y - 1) + (x - 1)] =
				colors[2] + 0x100 * colors[2] + 0x10000 * colors[2];
		}
	}
}

void		draw(t_mlx *m, int x)
{
	int		y;
	int		color;
	int		depth;
	int		texY;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		while (y < m->draw.start)
			put_pixel(&(m->img), x, y++, SKYBLUE);
		while (y >= m->draw.start && y < m->draw.end)
		{
			depth = y * 256 - WIN_HEIGHT * 128 + m->draw.lineheight * 128;
			texY = ((depth * 64) / m->draw.lineheight) / 256;
			color = m->texture.pat[m->texture.num][64 * texY + m->texture.texX];
			put_pixel(&(m->img), x, y++, color);
		}
		put_pixel(&(m->img), x, y++, GRAY);
	}
}

void		calc_lineheight(t_mlx *m, int side, int x)
{
	m->draw.lineheight = (int)(WIN_HEIGHT / m->pl.pWallDist);
	m->draw.start = -m->draw.lineheight / 2 + WIN_HEIGHT / 2;
	if (m->draw.start < 0)
        m->draw.start = 0;
	m->draw.end = m->draw.lineheight / 2 + WIN_HEIGHT / 2;
	if (m->draw.end >= WIN_HEIGHT)
        m->draw.end = WIN_HEIGHT - 1;
	m->texture.num = 0;
	if (side == 0 && m->pl.rayDirX < 0)
        m->texture.num = 1 ;
	if (side == 1 && m->pl.rayDirY < 0)
        m->texture.num = 2 ;
	if (side == 1 && m->pl.rayDirY > 0)
        m->texture.num = 3 ;
	draw(m, x);
}
