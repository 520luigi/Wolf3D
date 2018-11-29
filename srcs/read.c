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

//utilize read functions from my fdf, modified it for wolf3d slightly
void	append(int fd, t_mlx *m, char **tmp, char *filename)
{
	char	*line;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	j = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strsplit(line, ' ');
		free(line);
		i = -1;
		while (tmp[++i])
		{
			m->map[j][i] = ft_atoi(tmp[i]);
			if (m->map[j][i] > 100000)
				m->map[j][i] = 100000;
			else if (m->map[j][i] < -100000)
				m->map[j][i] = -100000;
		}
		ft_free_2d((void**)tmp);
		if (i != m->map_width)
			ft_puterror("Error, check file lengths!\n");
		j++;
	}
	close(fd);
}

void	read_input(t_mlx *m, char *filename, int fd)
{
	int		count;
	char	*line;
	char	**tmp;

	count = 0;
	if (!(get_next_line(fd, &line)))
		ft_puterror("Error, invalid file\n");
	if (!(tmp = ft_strsplit(line, ' ')))
		ft_puterror("Error, invalid file\n");
	free(line);
	while (tmp[count])
		count++;
	ft_free_2d((void**)tmp);
	m->map_width = count;
	count = 1;
	while ((get_next_line(fd, &line) > 0) && ++count)
		free(line);
	m->map_height = count;
	if (!(m->map = (int **)ft_memalloc(sizeof(int *) * m->map_height)))
		ft_puterror("Error, no map");
	count = -1;
	while (++count < m->map_height)
		m->map[count] = (int *)ft_memalloc(sizeof(int) * m->map_width);
	close(fd);
	append(fd, m, tmp, filename);
}
