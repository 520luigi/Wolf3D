/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:01:12 by szheng            #+#    #+#             */
/*   Updated: 2018/11/28 10:01:15 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define HEIGHT 1080
# define WIDTH 1920
# define ESCAPE 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125


//struct to save image and then put to screen...
typedef struct s_img
{
    void *ptr;
    char *str;
    int  bpp;
    int  size_line;
    int  endian;
}              t_img;


typedef struct s_mlx
{
    void *mlx;
    void *win;

    // map values
    int  **map; //grid
    int  map_width; //map width
    int  map_height; //map height

    t_img  img;

}              t_mlx;

#endif
