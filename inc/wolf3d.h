/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:28:34 by cdittric          #+#    #+#             */
/*   Updated: 2018/08/18 21:12:19 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "gnl.h"

# include "qwerty.h"
// NOTE: Window width and height are set in parse arguments.

# define DEFAULT_WINDOW_WIDTH 1200
# define DEFAULT_WINDOW_HEIGHT 800

typedef double			t_scal;

typedef struct			s_vec2 {
	t_scal	v[2];
}						t_vec2;

typedef struct			s_vec3 {
	t_scal	v[3];
}						t_vec3;

typedef struct			s_vec4 {
	t_scal	v[4];
}						t_vec4;

typedef struct			s_mat2 {
	t_scal	m[4];
}						t_mat2;

typedef struct			s_ivec {
	int		v[2];
}						t_ivec;

typedef struct s_map	t_map;

struct					s_map
{
	char	*path;
	int		**grid;
	t_ivec	dim;
	t_map	**self;
	t_map	*next;
};

typedef struct	s_img {
	void			*link;
	unsigned char	*buf;
	t_ivec			size;
	int				px_size;
	int				line;
	int				endian;
	int				line_draw_mode;
}				t_img;

typedef struct	s_win {
	void			*mlx;
	void			*win;
	t_img			img;
	int				w;
	int				h;
	t_ivec			size; //TODO: Delete size. Replaced by w and h.
	int				frame;
	t_scal			fps;
	unsigned long	frames[30];
}				t_win;

typedef struct			s_env
{
	void		*mlx;
	t_win		win;
	char		keys[512];
	int			button;
	t_ivec		mouse_pos;
	t_ivec		tmp_mouse_pos;
	int			timer;
	t_vec3		pos;
	t_vec2		rot;
	t_vec2		origin_rot;
	t_mat2		cam_mat;
	t_map		*map_list;
}				t_env;

void			init_environment(t_env *env);
void			end_environment(t_env *env, int status);
void			set_hooks(t_env *env);

int				loop_hook(t_env *env);

int				button_press_hook(int button, int x, int y, t_env *env);
int				button_release_hook(int button, int x, int y, t_env *env);
int				motion_hook(int x, int y, t_env *env);
int				key_press_hook(int key_code, t_env *env);
int				key_release_hook(int key_code, t_env *env);
void			move(t_env *env);

void			display(t_env *env);

t_scal			sqr(t_scal n);

t_vec3			vec3(t_scal x, t_scal y, t_scal z);
t_vec2			vec2(t_scal x, t_scal y);
t_ivec			ivec(int x, int y);

t_mat2			m2identity(void);
t_mat2			m2rotation(t_scal angle);
t_mat2			m2dot(t_mat2 m1, t_mat2 m2);
t_vec2			m2dotv2(t_mat2 m, t_vec2 v);

t_vec3			vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec_mult(t_vec3 v1, t_scal d);
t_scal			length(t_vec3 v1);
t_scal			scalar(t_vec3 v1, t_vec3 v2);

int				init_new_win(void *mlx, t_win *win, t_ivec size, char *title);
void			paint_window(t_win *win, int clear);

void			display_data_scal(t_win *win, char *name, t_scal data, int y);
void			display_data_vec2(t_win *win, char *name, t_vec2 data, int y);
void			display_data_vec3(t_win *win, char *name, t_vec3 data, int y);
void			display_data_str(t_win *win, char *name, char *data, int y);

void			init_new_image(void *mlx, t_img *img, t_ivec size);
void			img_px(t_img *img, unsigned int color, t_ivec pixel);
void			clear_img(t_img *img);

unsigned int	color_gradiant(unsigned int *colors, t_scal gradiant);
int				get_key_digit(int key_code);

void			read_map_list(t_env *env);
t_map			*delete_map(t_map *map);
t_map			*add_map(t_env *env, char *path);

#endif
