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
# define RED 0xFF0000
# define BLUE 0x00BFFF
# define SKYBLUE 0x0099db
# define WHITE 0xFFFFFF
# define GRAY  0x303030
# define ESCAPE 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define T 17
# define Y 16
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14

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
	int			texx; //not needed i think...
	double		od;
	double		dx;
	double		dy;
	double		opln;
	double		posx;
	double		posy;
	double		plnx;
	double		plny;
	double		sens;

	double		rayDirX;
	double		rayDirY;
    double		sideDistX;
    double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;

	double		pwalldist;
}				t_player;

typedef struct	s_movement //ok
{
	int			detect_mouse;
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			left_rotation;
	int			right_rotation;
	double		rotation_speed;
    int			x_old;
}				t_movement;

typedef struct  s_draw //ok
{
    int         lineheight;
    int         start;
    int         end;
}               t_draw;

typedef struct	s_texture //ok
{
	int			pat[4][4096];
	int			x;
	int			y;
    int         num;
}				t_texture;

typedef struct	s_mlx //need instruction toggle...
{
	void		*mlx;
	void		*win;
    int         minimap_toggle;
    int         mouse_toggle;

    t_point		pt1;
    t_point		pt2;
    t_img		img;
	t_img		minimap;
    t_map		map;
	t_player	player;
	t_movement	move;
    t_draw      draw;
	t_texture	texture;
}				t_mlx;

void			read_input(t_mlx *m, char *filename, int fd);
void            setup(t_mlx *m, char *filename);
int             exit_hook(void);
int				mouse_motion(int x, int y, t_mlx *m);
int				key_release(int key, t_mlx *m);
int				key_press(int key, t_mlx *m);
void			put_pixel(t_img *img, int x, int y, unsigned int color);
void			raycast(t_mlx *mlx);
void			calc_lineheight(t_mlx *mlx, int side, int x);
int				move_loop(t_mlx *mlx);
void			create_textures(t_mlx *mlx, int x, int y);

#endif
