/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:35:18 by szheng            #+#    #+#             */
/*   Updated: 2018/12/03 10:13:14 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		append(int fd, t_mlx *m, char **tmp, char *filename)
{
	char	*line;
	int		i;
	int		j;

	if (!(fd = open(filename, O_RDONLY)) || !(m->map.ht))
		ft_puterror("Error, invalid file\n");
	j = -1;
	while (++j < m->map.ht && get_next_line(fd, &line) == 1)
	{
		tmp = ft_strsplit(line, ' ');
		free(line);
		if (!(m->map.grid[j] = (int *)ft_memalloc(sizeof(int) * m->map.wd)))
			ft_puterror("Error, invalid map");
		i = -1;
		while (++i < m->map.wd)
			m->map.grid[j][i] = (i != 0 && i != m->map.wd - 1 && j != 0 &&
					j != m->map.ht - 1) ? ft_atoi(tmp[i]) : 1;
		ft_free_2d((void**)tmp);
	}
	close(fd);
}

void		read_input(t_mlx *m, char *filename, int fd)
{
	char	*line;
	char	**tmp;

	m->map.wd = 0;
	m->map.ht = -1;
	while (++m->map.ht >= 0 && get_next_line(fd, &line) == 1)
	{
		tmp = ft_strsplit(line, ' ');
		while (tmp[m->map.wd])
			m->map.wd++;
		ft_free_2d((void**)tmp);
		free(line);
	}
	close(fd);
	if (m->map.ht != m->map.wd)
		ft_puterror("Invalid file, only square maps are supported!\n");
	if (!(m->map.grid = (int **)ft_memalloc(sizeof(int *) * m->map.ht)))
		ft_puterror("Error, no map\n");
	append(fd, m, tmp, filename);
}
