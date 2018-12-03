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
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ESCAPE 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define T 17
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define RED 0xFF0000
# define BLUE 0x00BFFF

typedef struct	s_point //ok
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_img  //ok
{
	void		*ptr;
	char		*str;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_map //ok
{
	int			**grid;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_map;

typedef struct	s_player
{
	int			texx;
	double		od;
	double		dx;
	double		dy;
	double		opln;
	double		posx;
	double		posy;
	double		plnx;
	double		plny;
	double		sens;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	double		pwalldist;
}				t_player;

typedef struct	s_movement
{
	int			first_mouse_movement;
	int			f;
	int			b;
	int			l;
	int			r;
	int			l_rot;
	int			r_rot;
	int			x_old;
	double		rspeed;
}				t_movement;

typedef struct	s_tex
{
	int			col[4][4096];
	int			x;
	int			y;
}				t_tex;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
    int         toggle;

    t_point		pt1;
    t_point		pt2;
    t_img		img;
	t_img		minimap;
    t_map		map;
	t_player	p;
	t_movement	m;
	t_tex		tex;
}				t_mlx;

void			read_input(t_mlx *m, char *filename, int fd);
void            setup(t_mlx *m, char *filename);
int             exit_hook(void);

void			ft_raycaster(t_mlx *mlx);
void			find_lineheight(t_mlx *mlx, int side, int x);
int				key_release_hook(int key, t_mlx *mlx);
int				move_loop(t_mlx *mlx);
int				mouse_motion_hook(int x, int y, t_mlx *mlx);
int				key_press_hook(int key, t_mlx *mlx);
//void			light_pixel(t_img *img, int x, int y, unsigned int color);
void			light_pixel(t_img *img, int x, int y, unsigned int color);
void			build_textures(t_mlx *mlx); //look into how to make this a solid color of 4 kinds, no design needed just an easy version...

#endif
