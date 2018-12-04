/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:56:34 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 09:56:36 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		add_texture(t_player *p, int side)
{
	double wallx;

	if (side == 0)
		wallx = p->posy + p->pwalldist * p->rayDirY;
	else
		wallx = p->posx + p->pwalldist * p->rayDirX;
	wallx -= floor(wallx);
	p->texx = (int)(wallx * 64.0);
	if (side == 0 && p->rayDirX > 0)
		p->texx = 64 - p->texx - 1;
	if (side == 1 && p->rayDirY < 0)
		p->texx = 64 - p->texx - 1;
}

int			walldist(t_map *map, t_player *p, int stepx, int stepy)
{
	int		hit;
	int		side;

	hit = 0;
	while (hit == 0 && map->x < map->width - 1 && map->y < map->height - 1)
	{
		if (p->sideDistX < p->sideDistY)
		{
			p->sideDistX += p->deltaDistX;
			map->x += stepx;
			side = 0;
		}
		else
		{
			p->sideDistY += p->deltaDistY;
			map->y += stepy;
			side = 1;
		}
		(map->grid[map->x][map->y] != 0) ? hit = 1 : 0;
	}
	p->pwalldist = (side == 0) ?
			(map->x - p->posx + (1 - stepx) / 2) / p->rayDirX :
			(map->y - p->posy + (1 - stepy) / 2) / p->rayDirY;
	add_texture(p, side);
	return (side);
}

int			findwall(t_map *map, t_player *p)
{
	int		stepx;
	int		stepy;

	if (p->rayDirX < 0)
	{
		stepx = -1;
		p->sideDistX = (p->posx - map->x) * p->deltaDistX;
	}
	else
	{
		stepx = 1;
		p->sideDistX = (map->x + 1.0 - p->posx) * p->deltaDistX;
	}
	if (p->rayDirY < 0)
	{
		stepy = -1;
		p->sideDistY = (p->posy - map->y) * p->deltaDistY;
	}
	else
	{
		stepy = 1;
		p->sideDistY = (map->y + 1.0 - p->posy) * p->deltaDistY;
	}
	return (walldist(map, p, stepx, stepy));
}

void		ft_put_and_destroy_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img.ptr, 0, 0);
	mlx_destroy_image(m->mlx, m->img.ptr);
    if (!m->minimap_toggle)
    {
    	light_pixel(&(m->minimap), m->player.posx * 5, m->player.posy * 5, 0xCCFF00);
    	mlx_put_image_to_window(m->mlx, m->win, m->minimap.ptr,
    		WIN_WIDTH - m->map.width * 5 - 10, 10);
    	light_pixel(&(m->minimap), m->player.posx * 5, m->player.posy * 5, 0);
    }
    //the function above put the minimap on, make it toggable...
}

void		ft_raycaster(t_mlx *m)
{
	int		x;
	double	camerax;
	int		side;

	m->img.ptr = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img.str = mlx_get_data_addr(m->img.ptr, &(m->img.bpp),
			&(m->img.size_line), &(m->img.endian));
	m->img.bpp /= 8;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		camerax = 2 * x / (double)(WIN_WIDTH) - 1;
		m->player.rayDirX = m->player.dx + m->player.plnx * camerax;
		m->player.rayDirY = m->player.dy + m->player.plny * camerax;
		m->map.x = (int)(m->player.posx);
		m->map.y = (int)(m->player.posy);
		m->player.deltaDistX = fabs(1 / m->player.rayDirX);
		m->player.deltaDistY = fabs(1 / m->player.rayDirY);
		side = findwall(&m->map, &m->player);
		find_lineheight(m, side, x);
	}
	ft_put_and_destroy_img(m);
}
