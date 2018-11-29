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

int     deal_key(int key)
{
    if (key == 53)
        exit(0);
    return (0);
}

int		main(int ac, char **av)
{
    t_mlx m;
    int fd;

    if (ac != 2)
        ft_puterror("Usage: ./wolf3d <map>\n");
    if ((fd = open(av[1], O_RDONLY)) < 0)
        ft_puterror("Error, no file exist\n");
    read_input(&m, av[1], fd);
    setup(&m);
    print_map(&m, -1, -1, 0); ///function used to move the map...
    mlx_mouse_hook(m.win, deal_mouse, &m)
    mlx_key_hook(m.win, deal_key, &m);
    mlx_loop(m.mlx);
    return (0);
}
