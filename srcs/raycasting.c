/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
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
		wallx = p->posy + p->pwalldist * p->raydiry;
	else
		wallx = p->posx + p->pwalldist * p->raydirx;
	wallx -= floor(wallx);
	p->texx = (int)(wallx * 64.0);
	if (side == 0 && p->raydirx > 0)
		p->texx = 64 - p->texx - 1;
	if (side == 1 && p->raydiry < 0)
		p->texx = 64 - p->texx - 1;
}

int			walldist(t_map *map, t_player *p, int stepx, int stepy)
{
	int		hit;
	int		side;

	hit = 0;
	while (hit == 0 && map->x < map->width - 1 && map->y < map->height - 1)
	{
		if (p->sidedistx < p->sidedisty)
		{
			p->sidedistx += p->deltadistx;
			map->x += stepx;
			side = 0;
		}
		else
		{
			p->sidedisty += p->deltadisty;
			map->y += stepy;
			side = 1;
		}
		(map->grid[map->x][map->y] != 0) ? hit = 1 : 0;
	}
	p->pwalldist = (side == 0) ?
			(map->x - p->posx + (1 - stepx) / 2) / p->raydirx :
			(map->y - p->posy + (1 - stepy) / 2) / p->raydiry;
	add_texture(p, side);
	return (side);
}

int			findwall(t_map *map, t_player *p)
{
	int		stepx;
	int		stepy;

	if (p->raydirx < 0)
	{
		stepx = -1;
		p->sidedistx = (p->posx - map->x) * p->deltadistx;
	}
	else
	{
		stepx = 1;
		p->sidedistx = (map->x + 1.0 - p->posx) * p->deltadistx;
	}
	if (p->raydiry < 0)
	{
		stepy = -1;
		p->sidedisty = (p->posy - map->y) * p->deltadisty;
	}
	else
	{
		stepy = 1;
		p->sidedisty = (map->y + 1.0 - p->posy) * p->deltadisty;
	}
	return (walldist(map, p, stepx, stepy));
}

void		ft_put_and_destroy_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img.ptr, 0, 0);
	mlx_destroy_image(m->mlx, m->img.ptr);
    if (!m->toggle)
    {
    	light_pixel(&m->minimap, m->p.posx * 5, m->p.posy * 5, 0xCCFF00);
    	mlx_put_image_to_window(m->mlx, m->win, m->minimap.ptr,
    		WIN_WIDTH - m->map.width * 5 - 10, 10);
    	light_pixel(&m->minimap, m->p.posx * 5, m->p.posy * 5, 0);
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
		m->p.raydirx = m->p.dx + m->p.plnx * camerax;
		m->p.raydiry = m->p.dy + m->p.plny * camerax;
		m->map.x = (int)(m->p.posx);
		m->map.y = (int)(m->p.posy);
		m->p.deltadistx = fabs(1 / m->p.raydirx);
		m->p.deltadisty = fabs(1 / m->p.raydiry);
		side = findwall(&m->map, &m->p);
		find_lineheight(m, side, x);
	}
	ft_put_and_destroy_img(m);
}
