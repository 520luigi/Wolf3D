/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:35:18 by szheng            #+#    #+#             */
/*   Updated: 2018/11/27 20:35:20 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

// void		ft_mlx_init(t_mlx *m)
// {
// 	int		a;
// 	int		b;
//
// 	build_textures(m);
// 	m->m.first_mouse_movement = 1;
// 	m->p.dx = -1;
// 	m->p.plny = 0.9;
//     m->toggle = 0;
// 	a = m->map.width;
// 	b = m->map.height - 1;
//     //this checks for full map, so that players need to be on it. add this to setup portion of the map...
// 	while (m->map.grid[b][--a] != 0 && b > 0)
// 	{
// 		if (a <= 0)
// 		{
// 			a = m->map.width;
// 			b--;
// 		}
// 	}
// 	(b < 1) ? ft_puterror("Full map error\n") : 0;
// 	m->p.posx = a;
// 	m->p.posy = b;
// }

// void	append(int fd, t_mlx *m, char **tmp, char *filename)
// {
// 	char	*line;
// 	int		i;
// 	int		j;
//
// 	fd = open(filename, O_RDONLY);
// 	j = 0;
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		tmp = ft_strsplit(line, ' ');
// 		free(line);
// 		i = -1;
// 		while (tmp[++i])
// 		{
// 			m->map.grid[j][i] = ft_atoi(tmp[i]);
// 			if (m->map.grid[j][i] > 100000)
// 				m->map.grid[j][i] = 100000;
// 			else if (m->map.grid[j][i] < -100000)
// 				m->map.grid[j][i] = -100000;
// 		}
// 		ft_free_2d((void**)tmp);
// 		if (i != m->map.width)
// 			ft_puterror("Error, check file lengths!\n");
// 		j++;
// 	}
// 	close(fd);
// }

void		append(int fd, t_mlx *m, char **tmp, char *filename)
{
    char	*line;
	int		i;
    int     j;

	if (!(m->map.height) || !(fd = open(filename, O_RDONLY)))
		ft_puterror("Error, invalid file\n");
    j = -1;
	while (++j < m->map.height && get_next_line(fd, &line) == 1)
	{
		tmp = ft_strsplit(line, ' ');
        free(line);
		// i = 0;
		// while (tmp[i])
		// 	i++;
		// (i != m->map.width) ? ft_puterror("Error, map width error\n"): 0;
		if (!(m->map.grid[j] = (int *)ft_memalloc(sizeof(int) * m->map.width)))
			ft_puterror("Error, invalid map");
		i = -1;
		while (++i < m->map.width)
			m->map.grid[j][i] = (i != 0 && i != m->map.width - 1 && j != 0 &&
                j != m->map.height - 1) ? ft_atoi(tmp[i]) : 1;
		ft_free_2d((void**)tmp);
	}
	close(fd);
}

//ok
void		read_input(t_mlx *m, char *filename, int fd)
{
	char	*line;
	char	**tmp;

	m->map.width = 0;
	m->map.height = -1;
	while (++m->map.height >= 0 && get_next_line(fd, &line) == 1)
	{
		tmp = ft_strsplit(line, ' ');
		while (tmp[m->map.width])
			m->map.width++;
		ft_free_2d((void**)tmp);
		free(line);
	}
	close(fd);
    if (m->map.height != m->map.width)
        ft_puterror("Wolf3D only supports square maps!\n");
	if (!(m->map.grid = (int **)ft_memalloc(sizeof(int *) * m->map.height)))
		ft_puterror("Error, no map\n");
	append(fd, m, tmp, filename);
}
