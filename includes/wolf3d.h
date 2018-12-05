/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:01:12 by szheng            #+#    #+#             */
/*   Updated: 2018/12/05 11:14:15 by szheng           ###   ########.fr       */
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
# define I 34
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_img
{
	void		*ptr;
	char		*str;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_map
{
	int			**grid;
	int			wd;
	int			ht;
	int			x;
	int			y;
}				t_map;

typedef struct	s_player
{
	double		old_dir_x;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		old_plane_x;
	double		raydir_x;
	double		raydir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
}				t_player;

typedef struct	s_movement
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

typedef struct	s_draw
{
	int			lineheight;
	int			start;
	int			end;
}				t_draw;

typedef struct	s_texture
{
	int			texx;
	int			pat[4][4096];
	int			x;
	int			y;
	int			num;
}				t_texture;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			minimap_toggle;
	int			mouse_toggle;
	int			instruction_toggle;

	t_point		pt1;
	t_point		pt2;
	t_img		img;
	t_img		minimap;
	t_map		map;
	t_player	pl;
	t_movement	move;
	t_draw		draw;
	t_texture	texture;
}				t_mlx;

void			read_input(t_mlx *m, char *filename, int fd);
void			setup(t_mlx *m, char *filename);
int				exit_hook(void);
int				mouse_motion(int x, int y, t_mlx *m);
int				key_release(int key, t_mlx *m);
int				key_press(int key, t_mlx *m);
void			print_instructions(t_mlx *m);
void			put_pixel(t_img *img, int x, int y, unsigned int color);
void			raycast(t_mlx *mlx);
void			calc_lineheight(t_mlx *mlx, int side, int x);
int				movement_loop(t_mlx *mlx);
void			create_textures(t_mlx *mlx, int x, int y);

#endif
